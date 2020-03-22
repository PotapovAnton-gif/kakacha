#include "../interfaces/logic_client.h"
#include "../interfaces/network_client.h"

using namespace Network;
using namespace Network::Client;

namespace Logic::Client {


class LogicClientListener: public ClientListener {

public:

	LogicClientListener() {}
	~LogicClientListener() {}

	void onConnecting() {

		cout << "Connecting with server" << endl;

	}

	void onDropped(string reason) {

		cout << "Connection attempt failed because " << reason << endl;

	}

	void onConnected() {

		cout << "Connection established" << endl;

	}

	void onDisconnected(string reason) {

		cout << "OOPS, Disconnect cos" << reason << endl;

	}

	void onPacketReceived(Packet*) {

		cout << "This function have't worked yet" << endl;

	}

};


} /* namespace Logic::Client */
