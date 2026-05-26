#pragma once

#include "AbstractPatientDatabaseLoader.h"


// This is a simulated class. It does not really connect to the database, but
// for the sake of the assignment, pretend it does.
class PatientDatabaseLoader : public AbstractPatientDatabaseLoader {
public:

	// Inherited via AbstractPatientDatabaseLoader
	virtual void initialiseConnection() override;

	virtual void loadPatients(std::vector<Patient*>& patientIn) override;

	virtual void closeConnection() override;

};

