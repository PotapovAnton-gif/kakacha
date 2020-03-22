#ifndef SRC_INTERFACES_NETWORK_SERVER_H_
#define SRC_INTERFACES_NETWORK_SERVER_H_

#include "network_common.h"
#include "modules.h"

namespace Network {
namespace Server {

using namespace std;


class Client;

class ServerListener {

public:
	virtual ~ServerListener() {}

	/*
	 * Called when the server has started and is ready to accept clients.
	 */
	virtual void onServerStarted() = 0;

	/*
	 * Called when the server has stopped completely.
	 */
	virtual void onServerStopped() = 0;

	/*
	 * Called when a new connection is detected. This may not be a client yet.
	 * Returns false if the connection should be rejected.
	 */
	virtual bool onClientConnecting(string address) = 0;

	/*
	 * Called when a client has closed the connection before becoming ready to
	 * converse.
	 */
	virtual void onClientDropped(string address, string reason) = 0;

	/*
	 * Called when a new client has connected and is ready to converse.
	 */
	virtual void onClientConnected(Client*) = 0;

	/*
	 * Called when a client that was previously connected has disconnected.
	 */
	virtual void onClientDisconnected(Client*) = 0;

	/*
	 * Called when a new network packet is received.
	 */
	virtual void onPacketReceived(Client* sender, Packet*) = 0;

};


/*
 * Server Network Module
 */
class ServerNetworkModule : public Modules::Module {

public:

	/*
	 * A TCP port number.
	 */
	using Port = unsigned short int;

	ServerNetworkModule() : Modules::Module("Server-Network") {}
	virtual ~ServerNetworkModule() {}

	/*
	 * Sets the ServerListener to use. This module will delete the object on
	 * termination.
	 */
	virtual
	void
	setServerListener(ServerListener*)
	= 0;

	/*
	 * Gets the list of conversable clients.
	 */
	virtual
	const vector<Client*>&
	getClients()
	= 0;

	/*
	 * Returns the TCP port that this server is running on.
	 */
	virtual
	Port
	getPort()
	= 0;

	/*
	 * Stops the server. Clients are presented the specified message as the
	 * disconnect reason.
	 */
	virtual
	void
	stop(string message)
	= 0;

};

/*
 * Returns the Server-Network module.
 */
ServerNetworkModule& getServerNetwork();

/*
 * Registers the Server-Network module.
 * Internal use only -- do NOT invoke outside of registerModules()!
 */
void registerModule();


/*
 * A client that has connected to a server.
 */
class Client {
public:
	virtual ~Client();

	/*
	 * Returns the nickname of the client.
	 */
	virtual string getNickname() const;

	/*
	 * Sets the (local) nickname of this client.
	 */
	virtual void setNickname(string);

	/*
	 * Returns true if and only if the client is conversable.
	 */
	virtual bool isConversable() const;

	/*
	 * Returns the approximate network latency (ping) for this client
	 * in milliseconds.
	 */
	virtual Ping getPing() const;

	/*
	 * Returns the address of this client.
	 */
	virtual string getAddress() const;

	/*
	 * Sends the specified packet to the client. The provided object is deleted.
	 * Behaviour is undefined if the client is not conversable.
	 *
	 */
	virtual void sendPacket(Packet*);

	/*
	 * Disconnects the client from the server. This method returns after the TCP
	 * connection has been closed.
	 *
	 * message - the disconnect reason to display to the client.
	 */
	virtual void disconnect(string message);
};

/*
 * Prints a user-friendly representation of this client.
 */
ostream& operator<<(ostream&, const Client&);


} /* namespace Network::Server */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_SERVER_H_ */
