#pragma once

#include "Patient.h"
#include "PatientAlertObserver.h"


class GPNotificationSystemFacade : public PatientAlertObserver
{
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	void sendGPNotificationForPatient(Patient* p);

	// PatientAlertObserver hook: forwarded to sendGPNotificationForPatient
	// so that alert-level changes drive the existing facade behaviour.
	void onAlertLevelChanged(Patient* p) override;
};

