#ifndef SRC_INTERFACES_NETWORK_CLIENT_H_
#define SRC_INTERFACES_NETWORK_CLIENT_H_

#include "network_common.h"
#include "modules.h"

namespace Network {
namespace Client {


class ClientListener {
public:

	virtual ~ClientListener() {}

	/*
	 * Called when a connection attempt is made.
	 */
	virtual void onConnecting() = 0;

	/*
	 * Called when a connection attempt has failed.
	 */
	virtual void onDropped(string reason) = 0;

	/*
	 * Called when a connection is established and the server is ready
	 * to converse.
	 */
	virtual void onConnected() = 0;

	/*
	 * Called when the connection has been terminated.
	 */
	virtual void onDisconnected(string reason) = 0;

	/*
	 * Called when a new network packet is received.
	 */
	virtual void onPacketReceived(Packet*) = 0;
};

/*
 * Client Network Module
 */
class ClientNetworkModule : public Modules::Module {
public:

	ClientNetworkModule() : Modules::Module("Client-Network") {}
	virtual ~ClientNetworkModule() {}

	/*
	 * Sets the ClientListener to use. This module will delete the object on
	 * termination.
	 */
	virtual
	void
	setClientListener(ClientListener*)
	= 0;

	/*
	 * Connects to the specified address. This method returns after the TCP
	 * connection has been established or closed, i.e. the client is not
	 * necessarily conversable (see Client::isConversable()).
	 *
	 * Behaviour is undefined if the client is already connected.
	 *
	 * address - the address to connect to. Ex.: "windcorp.ru:25565".
	 * nickname - the initial nickname to use.
	 */
	virtual
	void
	connect(string address, string nickname)
	= 0;

	/*
	 * Disconnects from the server. This method returns after the TCP connection
	 * has been closed.
	 *
	 * Behaviour is undefined if the server is not conversable.
	 */
	virtual
	void
	disconnect()
	= 0;

	/*
	 * Returns the address that this client is connected to.
	 */
	virtual
	string
	getAddress()
	= 0;

	/*
	 * Returns true if and only if the server is conversable.
	 */
	virtual
	bool
	isConversable()
	= 0;

	/*
	 * Returns true if and only if a TCP connection exists.
	 */
	virtual
	bool
	isConnected()
	= 0;

	/*
	 * Sends the specified packet to the server. The provided object is deleted.
	 * Behaviour is undefined if the server is not conversable.
	 */
	virtual
	void
	sendPacket(Packet*)
	= 0;

};

/*
 * Returns the Client-Network module.
 */
ClientNetworkModule& getClientNetwork();

/*
 * Registers the Client-Network module.
 * Internal use only -- do NOT invoke outside of registerModules()!
 */
void registerModule();


} /* namespace Network::Client */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_CLIENT_H_ */
