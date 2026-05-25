#pragma once

class Patient;


// Observer interface for parties that want to react to a Patient's alert
// level changing. Concrete observers register themselves on individual
// Patient objects through Patient::registerAlertObserver.
class PatientAlertObserver
{
public:
	virtual ~PatientAlertObserver() = default;
	virtual void onAlertLevelChanged(Patient* patient) = 0;
};
