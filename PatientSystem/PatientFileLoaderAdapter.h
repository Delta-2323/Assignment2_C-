#pragma once

#include <memory>
#include <string>

#include "AbstractPatientDatabaseLoader.h"

class PatientFileLoader;

// Adapter that lets the file-based PatientFileLoader plug into any code
// that expects an AbstractPatientDatabaseLoader. The PatientFileLoader
// header is part of the assignment-fixed interface and cannot be modified,
// so the adaptation lives entirely on this side.
class PatientFileLoaderAdapter : public AbstractPatientDatabaseLoader
{
public:
	explicit PatientFileLoaderAdapter(const std::string& filename);
	~PatientFileLoaderAdapter() override;

	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientsIn) override;
	void closeConnection() override;

private:
	std::string _filename;
	std::unique_ptr<PatientFileLoader> _fileLoader;
};
