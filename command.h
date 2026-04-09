#pragma once

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <utility>

enum class CommandEnum {
	Exit = 0,
	Help,
	Time,
	Greet,
	YellSomething,
	ReverseString,
	Unknown
};

class Command {
public:
	virtual void execute() = 0;
	virtual ~Command() = default;
};

class Invoker {
public: 
	Invoker(std::unique_ptr<Command> cmd) : cmd_(std::move(cmd)) {};
	~Invoker() = default;

	void invoke() {
		cmd_->execute();
	}
private:
	std::unique_ptr<Command> cmd_;
};


class Help : public Command {
public:
	void execute() {
		std::cout << "List of available commands (case sensitive): " << std::endl;
		std::cout << "time: for getting current time" << std::endl;
		std::cout << "greet: for greeting" << std::endl;
		std::cout << "time: for getting current time" << std::endl;
		std::cout << "yell: for YELLING SOMETHING LOUD" << std::endl;
		std::cout << "reverse: for reversing your message" << std::endl;
		std::cout << "exit: to stop this application" << std::endl;
	}
};

class Time : public Command {
public:
	void execute() override {
		auto time_now = std::chrono::system_clock::now();
		std::cout << "Current UTC time is: " << time_now << std::endl;
	}
};

class Exit : public Command {
public:
	void execute() override {
		std::cout << "Bye. Thank you for using REPL!" << std::endl;
		std::exit(0);
	}
};

class Greet : public Command {
public:
	Greet(std::string person_name) : person_name_(person_name) {}
	void execute() override {
		if(person_name_.size() > 0) std::cout << "Salutations, dear " << person_name_ << std::endl;
		else std::cout << "Salutations, dear incognito" << std::endl;
	}
private:
	std::string person_name_;
};

class UnknownCommand : public Command {
public:
	UnknownCommand(std::string command) : command_(command) {};
	void execute() override {
		std::cout << command_ << " is unknown command" << std::endl;
	}
private:
	std::string command_;
};

class YellSomething : public Command {
public :
	YellSomething(std::string string_to_yell) : string_to_yell_(string_to_yell) {}
	void execute() override {
		for (char& c : string_to_yell_) c = std::toupper(c);
		std::cout << string_to_yell_ << std::endl;
	}
private:
	std::string string_to_yell_;
};

class ReverseString : public Command {
public:
	ReverseString(std::string string_to_reverse) : string_to_reverse_(string_to_reverse) {}
	void execute() override {		
		std::reverse(string_to_reverse_.begin(), string_to_reverse_.end());
		std::cout << string_to_reverse_ << std::endl;
	}
private:
	std::string string_to_reverse_;
};


