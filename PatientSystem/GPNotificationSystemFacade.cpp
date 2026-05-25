#include "GPNotificationSystemFacade.h"

#include <iostream>


GPNotificationSystemFacade::GPNotificationSystemFacade()
{ }

GPNotificationSystemFacade::~GPNotificationSystemFacade()
{ }

void GPNotificationSystemFacade::sendGPNotificationForPatient(Patient* p)
{
	if (p->alertLevel() > AlertLevel::Orange) {
		// A mocked alert message. A real message would use an SMS/pager gateway or similar
		std::cout << std::endl;
		std::cout << "This is an notification to the GPs:" << std::endl;
		std::cout << "Patient: " << p->humanReadableID() << " should be followed up" << std::endl;
	}
}

void GPNotificationSystemFacade::onAlertLevelChanged(Patient* p)
{
	sendGPNotificationForPatient(p);
}
