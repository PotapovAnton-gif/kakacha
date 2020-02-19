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
	virtual void onClientDropped(string address) = 0;

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
	ServerNetworkModule();
	virtual ~ServerNetworkModule();

	/*
	 * Sets the ServerListener to use.
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
	 * Stops the server. Clients are presented the specified message as the
	 * disconnect reason.
	 */
	virtual
	void
	stop(string message)
	= 0;

};

ServerNetworkModule* getServerNetwork();


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
	 * Sets the nickname of this client.
	 */
	virtual void setNickname(string);

	virtual bool isConversable() const;
	virtual Ping getPing() const;
	virtual string getAddress() const;

	virtual void sendPacket(Packet*);
	virtual void disconnect(string message);
};

ostream& operator<<(ostream&, const Client&);


} /* namespace Network::Server */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_SERVER_H_ */
