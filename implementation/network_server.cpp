#include "../interfaces/network_server.h"

namespace Network::Server {


class ServerNetworkModuleImpl : public ServerNetworkModule {

private:

	vector<Client*> clients = vector<Client*>();
	Port port;

	ServerListener* listener = nullptr;

public:

	ServerNetworkModuleImpl(const ServerNetworkModuleImpl&) = delete;
	ServerNetworkModuleImpl& operator=(const ServerNetworkModuleImpl&) = delete;

	~ServerNetworkModuleImpl() {
		if (listener != nullptr)
			delete listener;

		for (Client* client : clients) {
			delete client;
		}
	}

	void
	doInitialize()
	override
	{
		cout << "[Server-Network] Initializing" << endl;
	}

	void
	doFinalize()
	override
	{
		cout << "[Server-Network] Finalizing" << endl;

		stop("Server shutting down");
	}

	virtual
	void
	setServerListener(ServerListener* listener)
	override
	{
		this->listener = listener;
		cout << "[Server-Network] Set listener" << endl;
	}

	virtual
	const vector<Client*>&
	getClients()
	override
	{
		return clients;
	}

	virtual
	Port
	getPort()
	override
	{
		return port;
	}

	virtual
	void
	stop(string message)
	override
	{
		cout << "[Server-Network] Stopping server" << endl;
	}

};

ServerNetworkModule *inst;


ServerNetworkModule& getServerNetwork() {
	return *inst;
}

void registerModule() {
	inst = new ServerNetworkModuleImpl();
	Modules::registerModule(inst);
}


} /* namespace Network::Server */
