#ifndef SRC_INTERFACES_MODULES_H_
#define SRC_INTERFACES_MODULES_H_

#include <string>

#include "common.h"

namespace Modules {

using std::string;


/*
 * A program module
 */
class Module {
public:
	/*
	 * Creates a new module with the specified name.
	 * Do not perform any lengthy tasks in the constructor!
	 */
	Module(string name);

	virtual ~Module();

	/*
	 * Returns the name of this module.
	 */
	virtual string getName();

	/*
	 * Returns true if this module has successfully been initialized.
	 */
	bool isInitialized();

	/*
	 * Initializes this module, performing all necessary tasks.
	 * Returns false if the initialisation has failed and the program must
	 * abort. In that case Module::finalize() will not be invoked.
	 */
	bool initialize();

	/*
	 * Finalizes this module before the program shuts down. This method will not
	 * be invoked unless Module::initialise() has been invoked successfully
	 * before.
	 */
	void finalize();

protected:

	/*
	 * Place logic for Module::initialize() here.
	 */
	virtual bool doInitialize() = 0;

	/*
	 * Place logic for Module::finalize() here.
	 */
	virtual void doFinalize() = 0;

private:
	string name;
	bool initialized = false;
};

/*
 * Registers a new module. This module will be handled by the launcher. The
 * pointer will be freed automatically.
 */
void registerModule(Module*);

/*
 * Returns a list of all regsitered modules.
 */
const std::vector<Module*> getModules();

/*
 * Attempts to initialize all registered modules by invoking
 * Module::initialize() on all objects. If any module fails to initialize,
 * calls Modules::finalizeModules() and returns false; otherwise returns true.
 */
bool initializeModules();

/*
 * Finalizes all registered modules that have initialized successfully by
 * invoking Module::finalize() on all objects that are Module::isInitialized(),
 * then deletes all objects and clears the module registry.
 */
void finalizeModules();

/*
 * Different launch modes.
 */
enum LaunchMode {
	/*
	 * This is a client.
	 */
	CLIENT,

	/*
	 * This is a server.
	 */
	SERVER,

	/*
	 * Launch mode is not yet known.
	 */
	UNKNOWN = -1
};

/*
 * Returns the current launch mode or UNKNOWN if launch mode has not been set
 * yet.
 */
LaunchMode getLaunchMode();

/*
 * Sets the launch mode.
 */
void setLaunchMode(LaunchMode);


} /* namespace Modules */

#endif /* SRC_INTERFACES_MODULES_H_ */
