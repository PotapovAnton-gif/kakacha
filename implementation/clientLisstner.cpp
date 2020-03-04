#include "network_common.h"
#include "modules.h"
#include "network_client.h"
#include "logic_client.h"

using namespace LogicClient;
using namespace Network;
using namespace Client;

class logicClientListener : public ClientListener {

	logicClientListener();
	~logicClientListener();

	void onConnecting();
	void onDropped(string reason);
	void onConnected();
	void onDisconnected(string reason);
	void onPacketReceived(Packet*);
};


void logicClientListener::onConnecting(){
		cout << "Connection with server";
		if (getClientNetwork()->isConnected() == false){
			onDropped(string reason);
		}
			else{
				cout << "Connect is stable";
			}
		}
	}
void logicClientListener::onDropped(string reason){
	cout << "Ñonnection attempt failed because " << reason << endl;
	}

void logicClientListener::onConnected(){
	cout << "Ñonnection established" << endl;


}
void logicClientListener::onDisconnected(string reason){
	cout << "OOPS, Disconnect cos" << reason;
}





