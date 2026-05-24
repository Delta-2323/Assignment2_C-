#pragma once

#include <memory>
#include <vector>

#include "AbstractPatientDatabaseLoader.h"


// Composite loader that delegates to a list of child loaders in order.
// Because it implements AbstractPatientDatabaseLoader itself, the rest of
// the system treats a composite of loaders identically to a single loader,
// which is the defining characteristic of the Composite pattern.
class CompositePatientLoader : public AbstractPatientDatabaseLoader
{
public:
	CompositePatientLoader();
	~CompositePatientLoader() override;

	// Take ownership of a child loader. Loaders are invoked in the order added.
	void addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader);

	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientsIn) override;
	void closeConnection() override;

private:
	std::vector<std::unique_ptr<AbstractPatientDatabaseLoader>> _loaders;
};
