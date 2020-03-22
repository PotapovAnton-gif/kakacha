#include "../interfaces/logic_client.h"

#include "../interfaces/network_client.h"

namespace Logic::Client {


class ClientLogicImpl : public ClientLogic {

private:


public:

	ClientLogicImpl() {}

	bool doInitialize() override {
		Network::Client::getClientNetwork().setClientListener(nullptr);
		return true;
	}

	void doFinalize() override {

	}

};


} /* namespace Logic::Client */
