#include "CompositePatientLoader.h"


CompositePatientLoader::CompositePatientLoader() = default;

CompositePatientLoader::~CompositePatientLoader() = default;

void CompositePatientLoader::addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader)
{
	if (loader) {
		_loaders.push_back(std::move(loader));
	}
}

void CompositePatientLoader::initialiseConnection()
{
	for (const auto& loader : _loaders) {
		loader->initialiseConnection();
	}
}

void CompositePatientLoader::loadPatients(std::vector<Patient*>& patientsIn)
{
	for (const auto& loader : _loaders) {
		loader->loadPatients(patientsIn);
	}
}

void CompositePatientLoader::closeConnection()
{
	for (const auto& loader : _loaders) {
		loader->closeConnection();
	}
}
