#pragma once

#include <vector>

// forward declare the Patient class
class Patient;

class AbstractPatientDatabaseLoader {
public:
	virtual ~AbstractPatientDatabaseLoader() = default;

	// initialise the database connection
	virtual void initialiseConnection() = 0;

	// load patients from that database.
	// This method should allocated dynamic (i.e. new-ed) Patients into
	// the vector reference. The fucntion caller must take responsibilty for
	// cleaning up the memory.
	virtual void loadPatients(std::vector<Patient*>& patientIn) = 0;

	virtual void closeConnection() = 0;
};