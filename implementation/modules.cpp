#include <iostream>

#include "modules.h"


// ------------
// Module class
// ------------

using namespace std;
using namespace Modules;


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
