#ifndef SRC_INTERFACES_LOGIC_CLIENT_H_
#define SRC_INTERFACES_LOGIC_CLIENT_H_

#include "network_common.h"
#include "modules.h"
#include "network_client.h"

using namespace Network;
using namespace Modules;

namespace LogicClient {


class LogicClient : public Module {

	LogicClient();
	virtual ~LogicClient(){}



};


}

#endif /* SRC_INTERFACES_LOGIC_CLIENT_H_ */
