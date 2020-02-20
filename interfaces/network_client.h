#ifndef SRC_INTERFACES_NETWORK_CLIENT_H_
#define SRC_INTERFACES_NETWORK_CLIENT_H_

#include "network_common.h"
#include "modules.h"

namespace Network {
namespace Client {


class ClientListener {
	virtual ~ClientListener() {}

	virtual void onConnecting() = 0;
	virtual void onDropped() = 0;
	virtual void onConnected() = 0;
	virtual void onDisconnected(string reason) = 0;

	virtual void onPacketReceived(Packet*) = 0;
};

class ClientNetworkModule : public Modules::Module {
public:

	ClientNetworkModule() : Modules::Module("Client-Network") {}
	virtual ~ClientNetworkModule() {}

	virtual
	void
	setClientListener(ClientListener*)
	= 0;

	virtual
	void
	connect(string address, string nickname)
	= 0;

	virtual
	void
	disconnect()
	= 0;

	virtual
	string
	getAddress()
	= 0;

	virtual
	bool
	isConversable()
	= 0;

	virtual
	void
	sendPacket(Packet*)
	= 0;

};

ClientNetworkModule* getClientNetwork();


} /* namespace Network::Client */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_CLIENT_H_ */
