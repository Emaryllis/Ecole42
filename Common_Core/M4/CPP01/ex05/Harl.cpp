#include "Harl.hpp"
#include <iostream>

void Harl::debug() const {
	std::cout <<
		"Why am I doing this extra work? I already know how to do it. This is so so so frustrating!"
		<< std::endl;
}

void Harl::info() const {
	std::cout <<
		"I cannot believe that I'm doing this. I have to do something that I already know? This is ridiculous!"
		<< std::endl;
}

void Harl::warning() const {
	std::cout <<
		"I think I deserve some credit for doing this extra work. It's not fair that I have to do something I already know."
		<< std::endl;
}

void Harl::error() const {
	std::cout << "This is unacceptable! I would like to lodge a complaint!"
		<< std::endl;
}

void Harl::complain(const std::string &level) const {
	const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*ptr[4])() const = {&Harl::debug, &Harl::info, &Harl::warning,
									&Harl::error};
	for (int i = 0; i < 4; i++) {
		if (level == levels[i])
			(this->*ptr[i])();
	}
}
