#ifndef SRC_INTERFACES_COMMANDS_H_
#define SRC_INTERFACES_COMMANDS_H_

#include <iostream>
#include <unordered_map>

namespace Commands{

class Commands{

public:

	Commands();
	// make a table
	virtual ~Commands() = 0;

	virtual void initialize() = 0;
	// fill table with commands and functions

	virtual bool ifTableHaveThatCommand(std::string command) = 0;

	virtual bool ifThisCommand(std::string name) = 0;

	virtual void dothatcommand(std::string command) = 0;

};

}



#endif /* SRC_INTERFACES_COMMANDS_H_ */
