#ifndef SRC_INTERFACES_CONFIG_H_
#define SRC_INTERFACES_CONFIG_H_

#include "modules.h"

using namespace Modules;

namespace Config{


class Config : public Module{

		Config();
		virtual ~Config();

		virtual string getString(string name) = 0;

		virtual int getInteger(string name) = 0;




	};
}

#endif /* SRC_INTERFACES_CONFIG_H_ */
