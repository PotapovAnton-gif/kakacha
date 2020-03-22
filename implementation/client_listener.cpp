#include "network_common.h"
#include "modules.h"
#include "network_client.h"
#include "logic_client.h"

using namespace LogicClient;
using namespace Network;
using namespace Client;

class LogicClientListener: public ClientListener {

	LogicClientListener();
	~LogicClientListener();

	void onConnecting();

	void onDropped(string reason);

	void onConnected();

	void onDisconnected(string reason);

	void onPacketReceived(Packet*);

};

void LogicClientListener::onConnecting() {

	cout << "Connecting with server" << endl;

}

void LogicClientListener::onDropped(string reason) {

	cout << "Connection attempt failed because " << reason << endl;

}

void LogicClientListener::onConnected() {

	cout << "Connection established" << endl;

}

void LogicClientListener::onDisconnected(string reason) {

	cout << "OOPS, Disconnect cos" << reason << endl;

}

void onPaketonPacketReceived(Packet*) {

	cout << "This function have't worked yet" << endl;

}

