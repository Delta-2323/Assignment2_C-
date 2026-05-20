#include "PatientFileLoaderAdapter.h"

#include "Patient.h"
#include "PatientFileLoader.h"


PatientFileLoaderAdapter::PatientFileLoaderAdapter(const std::string& filename) :
	_filename(filename),
	_fileLoader(std::make_unique<PatientFileLoader>())
{
}

PatientFileLoaderAdapter::~PatientFileLoaderAdapter() = default;

void PatientFileLoaderAdapter::initialiseConnection()
{
	// File-based loading does not require a long-lived connection.
}

void PatientFileLoaderAdapter::loadPatients(std::vector<Patient*>& patientsIn)
{
	std::vector<Patient*> loaded = _fileLoader->loadPatientFile(_filename);
	patientsIn.insert(patientsIn.end(), loaded.begin(), loaded.end());
}

void PatientFileLoaderAdapter::closeConnection()
{
	// Nothing to close for file-based loading.
}
