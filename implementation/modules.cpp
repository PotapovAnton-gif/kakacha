#include <iostream>

#include "../interfaces/modules.h"

namespace Modules {


// ------------
// Module class
// ------------

Module::Module(string name) :
	name(name)
{}

Module::~Module() {}

string Module::getName() {
	return name;
}

bool Module::isInitialized() {
	return initialized;
}

bool Module::initialize() {
	if (isInitialized()) {
		cerr << "Attempted to initialize module "
				<< getName() << " that was initialized previously" << endl;
		return false;
	}

	bool result = doInitialize();

	if (result) {
		initialized = true;
	}

	return result;
}

void Module::finalize() {
	if (!isInitialized()) {
		cerr << "Attempted to finalize module "
				<< getName() << " that was never initialized" << endl;
		return;
	}

	doFinalize();
}


// ---------------
// Module registry
// ---------------

vector<Module*> MODULES;

void registerModule(Module* module) {
	MODULES.push_back(module);
}

const vector<Module*>& getModules() {
	return MODULES;
}

bool initializeModules() {
	bool success = true;

	for (Module *module : MODULES) {
		if (!module->initialize()) {
			success = false;
			break;
		}
	}

	if (!success) {
		finalizeModules();
	}

	return success;
}

void finalizeModules() {
	for (
			auto iterator = MODULES.rbegin();
			iterator != MODULES.rend();
			iterator++
	) {
		Module& module = **iterator;
		if (module.isInitialized()) {
			module.finalize();
		}
	}

	for (Module* module : MODULES) {
		delete module;
	}

	MODULES.clear();
}


// ----------
// LaunchMode
// ----------

LaunchMode launchMode = UNKNOWN;

LaunchMode getLaunchMode() {
	return launchMode;
}

void setLaunchMode(LaunchMode mode) {
	launchMode = mode;
}


} /* namespace Modules */
