#pragma once

#include "Patient.h"
#include "PatientAlertObserver.h"


class HospitalAlertSystemFacade : public PatientAlertObserver
{
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();

	void sendAlertForPatient(Patient* p);

	// PatientAlertObserver hook: forwarded to sendAlertForPatient so that
	// alert-level changes drive the existing facade behaviour.
	void onAlertLevelChanged(Patient* p) override;
};

