#include "../interfaces/logic_client.h"

namespace LogicClient {



class LogicClientImpl : public LogicClient {

private:
public:
	LogicClientImpl() {}

	bool doInitialize() override;
	void doFinalize() override;

};

bool LogicClientImpl::doInitialize() {
	Network::Client::getClientNetwork()->setClientListener(nullptr);
	return true;
}
void LogicClientImpl::doFinalize() {
}

}
