#include <iostream>

#include "../interfaces/modules.h"

using std::cout;
using std::endl;


void registerModules();
void processArguments(int argumentCount, char** arguments);

int main(int argumentCount, char** arguments) {

	processArguments(argumentCount, arguments);

	registerModules();

	Modules::initializeModules();

}

void processArguments(int argumentCount, char** /*arguments*/) {
	// This is a stab
	// TODO parse arguments

	using namespace Modules;

	if (argumentCount == 0) {
		setLaunchMode(CLIENT);
		cout << "Starting in client mode" << endl;
	} else {
		setLaunchMode(SERVER);
		cout << "Starting in server mode" << endl;
	}
}

#include "../interfaces/network_client.h"
#include "../interfaces/network_server.h"

void registerModules() {
	using namespace Modules;

	if (getLaunchMode() == SERVER) {
		Network::Server::registerModule();
	} else {
		Network::Client::registerModule();
	}

}
