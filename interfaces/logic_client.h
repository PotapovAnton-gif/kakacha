#ifndef SRC_INTERFACES_LOGIC_CLIENT_H_
#define SRC_INTERFACES_LOGIC_CLIENT_H_

#include "modules.h"

namespace Logic::Client {


class ClientLogic : public Modules::Module {

public:

	ClientLogic();
	virtual ~ClientLogic(){}

};


} /* namespace Logic::Client */

#endif /* SRC_INTERFACES_LOGIC_CLIENT_H_ */
