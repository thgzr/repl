#include <iostream>

#include "input.h"
#include "tokenizer.h"


int main()
{	
	std::cout << "type help to see command list" << std::endl;
	while (1) {
		std::string input = askForInput();
		std::string command;
		std::string argument;
		parseInput(input, command, argument);
		
		try {
			Invoker i(commandToPtr(command, argument));
			i.invoke();
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
   }
}
