#pragma once
#include "Person.h"

#include <memory>
#include <vector>

#include "PatientAlertLevels.h"


// forward declare classes
class Vitals;
class AlertLevelStrategy;
class PatientAlertObserver;

class Diagnosis {
public:
	static const std::string CORDYCEPS_BRAIN_INFECTION;
	static const std::string KEPRALS_SYNDROME;
	static const std::string ANDROMEDA_STRAIN;
};

class Patient : public Person {
public:

	Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);
	~Patient();

	// return a calculated age for the patient
	// this calculation is not accurate, but is suitable for assignment purposes
	int age() const;

	// return a "unique" ID generated for the patient
	// this id is generated purely from patient details, and as such may have collisions
	std::string uid() const;
	
	// returns a "nice" ID for humans to interpret: lastname, firstname (UID)
	std::string humanReadableID() const;

	// patients have diagnoses of a disease
	// Note: the initial design consider multiple diagnoses added using addDiagnosis.
	// This was refactored to only consider the primary (i.e. the first) diagnosis.
	// Adding a diagnosis also selects the matching alert level strategy.
	void addDiagnosis(const std::string& diagnosis);
	const std::string& primaryDiagnosis() const;

	// Add a vitals reading to the patient's history without recomputing the
	// alert level. Used by loaders for historical data.
	void addVitals(const Vitals* v);

	// Record a brand-new vitals reading: stores it and triggers the alert
	// level strategy. Use this for live readings entered through the UI.
	void recordVitals(const Vitals* v);

	const std::vector<const Vitals*> vitals() const;

	// patients have an alert level (green, yellow, orange, red) calculated from their disease and and their last vitals
	void setAlertLevel(AlertLevel level);
	AlertLevel alertLevel() const { return _alertLevel; }

	// Register an external observer that wants to be notified whenever the
	// patient's alert level changes. Patient does not own the observer.
	void registerAlertObserver(PatientAlertObserver* observer);

protected:
	std::vector<std::string> _diagnosis;
	std::vector<const Vitals*> _vitals;
	AlertLevel _alertLevel;

	std::unique_ptr<AlertLevelStrategy> _alertStrategy;
	std::vector<PatientAlertObserver*> _alertObservers;

	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

