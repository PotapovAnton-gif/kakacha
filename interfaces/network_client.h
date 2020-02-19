#ifndef SRC_INTERFACES_NETWORK_CLIENT_H_
#define SRC_INTERFACES_NETWORK_CLIENT_H_

#include "network_common.h"

namespace Network {
namespace Client {


void connect(string address, string nickname);
void disconnect();
bool isConnected();

void sendPacket(Packet*);


} /* namespace Network::Client */
} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_CLIENT_H_ */
