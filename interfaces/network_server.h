#ifndef SRC_INTERFACES_NETWORK_SERVER_H_
#define SRC_INTERFACES_NETWORK_SERVER_H_

#include "network_common.h"

namespace Network {
namespace Server {

using namespace std;


class Client {
private:
public:
	string getNickname() const;
	bool isConnected() const;
	Ping getPing() const;
	string getAddress() const;

	void sendPacket(Packet*);
	void disconnect(string message);
};

ostream& operator<<(ostream&, const Client&);

const vector<Client*>& getClients();
void shutdown(string message);


} /* namespace Network::Server */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_SERVER_H_ */
