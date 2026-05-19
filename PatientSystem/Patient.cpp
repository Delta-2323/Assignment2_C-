#include "Patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "AlertLevelStrategy.h"
#include "PatientAlertObserver.h"
#include "Vitals.h"


using namespace std;

const std::string Diagnosis::CORDYCEPS_BRAIN_INFECTION = "Cordyceps Brain Infection";
const std::string Diagnosis::KEPRALS_SYNDROME = "Kepral\xE2\x80\x99s Syndrome"; // UTF-8 right single quote
const std::string Diagnosis::ANDROMEDA_STRAIN = "Andromeda Strain";


Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green),
	_alertStrategy(std::make_unique<DefaultAlertStrategy>())
{
}

Patient::~Patient()
{
	// Patient owns its Vitals (allocated by loaders and recordVitals).
	for (const Vitals* v : _vitals) {
		delete v;
	}
	_vitals.clear();
}

int Patient::age() const
{	
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0)) 
	   << (char)std::tolower(_firstName.at(0))
	   << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
	   << _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();
	
	os << "|";
	for (size_t i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);

	// Pick the alert level strategy that matches the (primary) diagnosis.
	// We only do this for the first diagnosis to keep the existing
	// "primary diagnosis" semantics.
	if (_diagnosis.size() == 1) {
		if (diagnosis == Diagnosis::CORDYCEPS_BRAIN_INFECTION) {
			_alertStrategy = std::make_unique<CordycepsAlertStrategy>();
		}
		else if (diagnosis == Diagnosis::KEPRALS_SYNDROME) {
			_alertStrategy = std::make_unique<KepralsAlertStrategy>();
		}
		else if (diagnosis == Diagnosis::ANDROMEDA_STRAIN) {
			_alertStrategy = std::make_unique<AndromedaAlertStrategy>();
		}
		else {
			_alertStrategy = std::make_unique<DefaultAlertStrategy>();
		}
	}
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

void Patient::addVitals(const Vitals* v)
{
	// Historical reading: store only, do not recompute alert level.
	_vitals.push_back(v);
}

void Patient::recordVitals(const Vitals* v)
{
	// Live reading: store and recompute the alert level via the strategy.
	_vitals.push_back(v);
	const AlertLevel newLevel = _alertStrategy->computeAlertLevel(*this, *v);
	setAlertLevel(newLevel);
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;

	if (_alertLevel > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		default:
			break;
		}
		cout << endl;
	}

	// Notify observers after the level is updated so they observe the new
	// state via the patient. Observers decide whether the change is worth
	// acting on (e.g. only Red is escalated to hospitals).
	for (PatientAlertObserver* observer : _alertObservers) {
		observer->onAlertLevelChanged(this);
	}
}

void Patient::registerAlertObserver(PatientAlertObserver* observer)
{
	if (observer != nullptr) {
		_alertObservers.push_back(observer);
	}
}
