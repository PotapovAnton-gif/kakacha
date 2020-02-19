#include <iostream>

#include "../interfaces/modules.h"

using std::cout;
using std::endl;


int main(int argumentCount, char** arguments) {
	cout << "Lol" << endl;

	cout << argumentCount << " args: ";
	for (int i = 0; i < argumentCount; ++i) {
		if (i != 0) {
			cout << ", ";
		}

		cout << "\"" << arguments[i] << "\"";
	}
}
