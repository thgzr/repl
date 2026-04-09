#include <iostream>

#include "input.h"

int main()
{
	while (1) {
		std::string input = askForInput();
		std::string command;
		std::string argument;
		parseInput(input, command, argument);
		
		Invoker i(commandToPtr(command, argument));
		i.invoke();
   }
}
