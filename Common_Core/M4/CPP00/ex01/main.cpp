#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main() {
	std::string cmd;
	PhoneBook phoneBook = PhoneBook();
	while (cmd != "EXIT") {
		cmd = phoneBook.getNonEmptyString(
			"Enter a command (ADD, SEARCH, EXIT): ");
		if (cmd == "ADD") {
			phoneBook.addContactPrompt();
		} else if (cmd == "SEARCH") {
			phoneBook.searchContact();
		} else if (cmd != "EXIT") {
			std::cout << "Unknown command. Please try again." << std::endl;
		}
	}
	return 0;
}
