#include "../interfaces/network_client.h"

namespace Network::Client {


class ClientNetworkModuleImpl : public ClientNetworkModule {

private:

	string address;

	ClientListener* listener = nullptr;

public:

	ClientNetworkModuleImpl() {}
	ClientNetworkModuleImpl(const ClientNetworkModuleImpl&) = delete;
	ClientNetworkModuleImpl& operator=(const ClientNetworkModuleImpl&) = delete;

	~ClientNetworkModuleImpl() {
		if (listener != nullptr)
			delete listener;
	}

	bool
	doInitialize()
	override
	{
		cout << "[Client-Network] Initializing" << endl;
		return true;
	}

	void
	doFinalize()
	override
	{
		cout << "[Client-Network] Finalizing" << endl;
	}

	virtual
	void
	setClientListener(ClientListener* listener)
	override
	{
		this->listener = listener;
		cout << "[Client-Network] Set listener" << endl;
	}

	virtual
	void
	connect(string address, string nickname)
	override
	{
		cout << "[Client-Network] Connecting to "
				<< address << " with nickname "
				<< nickname << endl;

		this->address = address;

		if (listener == nullptr) {
			cout << "[Client-Network] No listener set" << endl;
			return;
		}

		cout << "[Client-Network] Invoking ClientListener::onConnecting()" << endl;
		listener->onConnecting();

		cout << "[Client-Network] I have connected" << endl;
		listener->onConnected();
	}

	virtual
	void
	disconnect()
	override
	{
		cout << "[Client-Network] Disconnecting..." << endl;
	}

	virtual
	string
	getAddress()
	override
	{
		return address;
	}

	virtual
	bool
	isConversable()
	override
	{
		return false;
	}

	virtual
	bool
	isConnected()
	override
	{
		return false;
	}

	virtual
	void
	sendPacket(Packet*)
	{
		cout << "[Client-Network] Sending packet" << endl;
	}

};

ClientNetworkModule *inst;


ClientNetworkModule& getClientNetwork() {
	return *inst;
}

void registerModule() {
	inst = new ClientNetworkModuleImpl();
	Modules::registerModule(inst);
}


} /* namespace Network::Server */
