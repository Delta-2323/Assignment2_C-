#include "PatientManagementSystem.h"

#include <iostream>
#include <limits>
#include <map>
#include <tuple>

#include "CompositePatientLoader.h"
#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "PatientFileLoaderAdapter.h"
#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"

using namespace std;


// Helper that builds the loader the system runs with. To swap loaders, change
// this single line in the constructor below to one of:
//   makeDatabaseOnlyLoader()
//   makeFileOnlyLoader()
//   makeDatabaseAndFileLoader()  <-- default per the assignment specification.
namespace {

	std::unique_ptr<AbstractPatientDatabaseLoader> makeDatabaseOnlyLoader()
	{
		return std::make_unique<PatientDatabaseLoader>();
	}

	std::unique_ptr<AbstractPatientDatabaseLoader> makeFileOnlyLoader()
	{
		return std::make_unique<PatientFileLoaderAdapter>("patients.txt");
	}

	std::unique_ptr<AbstractPatientDatabaseLoader> makeDatabaseAndFileLoader()
	{
		auto composite = std::make_unique<CompositePatientLoader>();
		composite->addLoader(std::make_unique<PatientDatabaseLoader>());
		composite->addLoader(std::make_unique<PatientFileLoaderAdapter>("patients.txt"));
		return composite;
	}
}


PatientManagementSystem::PatientManagementSystem() :
	_patientDatabaseLoader(makeDatabaseAndFileLoader()),
	_hospitalAlertSystem(std::make_unique<HospitalAlertSystemFacade>()),
	_gpNotificationSystem(std::make_unique<GPNotificationSystemFacade>())
{
	_patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
	_patientDatabaseLoader->closeConnection();

	// clear patient memory
	for (Patient* p : _patients) {
		delete p;
	}
	_patients.clear();
}

void PatientManagementSystem::init()
{
	_patientDatabaseLoader->loadPatients(_patients);
	for (Patient* p : _patients) {
		_patientLookup[p->uid()] = p;

		// Subscribe the hospital and GP facades to alert level changes for
		// every patient. Both facades implement PatientAlertObserver and
		// individually decide whether the new level warrants action.
		p->registerAlertObserver(_hospitalAlertSystem.get());
		p->registerAlertObserver(_gpNotificationSystem.get());
	}
}

void PatientManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		cin >> option;

		// handle basic errors and end-of-input
		if (cin.eof()) {
			break;
		}
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printPatients();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		default:
			break;
		}
	}
}

void PatientManagementSystem::addVitalsRecord()
{
	cout << "Patients" << endl;
	printPatients();
	cout << endl;
	cout << "Enter the patient ID to declare vitals for > ";
	
	string pid { "" };
	cin >> pid;
	if (_patientLookup.count(pid)) {
		float bodyTemperature;
		int bloodPressure;
		int heartRate;
		int respitoryRate;

		cout << "enter body temperature: ";
		cin >> bodyTemperature;
		cout << "enter blood pressure: ";
		cin >> bloodPressure;
		cout << "enter heart rate: ";
		cin >> heartRate;
		cout << "enter respitory rate: ";
		cin >> respitoryRate;

		Vitals* v = new Vitals(bodyTemperature, bloodPressure, heartRate, respitoryRate);
		_patientLookup[pid]->recordVitals(v);
	}
	else {
		cout << "Patient not found" << endl;
	}
}

void PatientManagementSystem::printWelcomeMessage() const
{
	cout << "WELCOME TO HEALTHCO 3000" << endl;
	cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
	cout << endl << "Select an option:" << endl;
	cout << "1. List patients" << endl;
	cout << "2. Add vitals record" << endl;
	cout << "3. Quit" << endl;
	cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
	for (Patient* p : _patients) {
		std::cout << *p << std::endl;
	}
}
