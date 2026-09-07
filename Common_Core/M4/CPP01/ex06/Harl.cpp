#include "Harl.hpp"
#include <iostream>

void Harl::debug() const {
	std::cout <<
		"[DEBUG]\nWhy am I doing this extra work? I already know how to do it. This is so so so frustrating!\n"
		<< std::endl;
}

void Harl::info() const {
	std::cout <<
		"[INFO]\nI cannot believe that I'm doing this. I have to do something that I already know? This is ridiculous!\n"
		<< std::endl;
}

void Harl::warning() const {
	std::cout <<
		"[WARNING]\nI think I deserve some credit for doing this extra work. It's not fair that I have to do something I already know.\n"
		<< std::endl;
}

void Harl::error() const {
	std::cout <<
		"[ERROR]\nThis is unacceptable! I would like to lodge a complaint!\n"
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
