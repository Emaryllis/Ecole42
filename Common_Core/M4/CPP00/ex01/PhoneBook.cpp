#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> // atoi, exit

PhoneBook::PhoneBook() : contactCount(0) {
}

std::string PhoneBook::getNonEmptyString(const std::string &prompt) const {
	std::string input;
	while (true) {
		std::cout << prompt;
		if (!std::getline(std::cin, input)) {
			std::cin.clear();
			std::cout << "\nEnd of input detected. Exiting program.\n";
			exit(1);
		}
		if (input.empty()) {
			std::cout << "Input cannot be empty. Please try again.\n";
			continue;
		}

		return input;
	}
}

int PhoneBook::getNonEmptyInteger(const std::string &prompt) const {
	int number;
	bool valid;

	do {
		valid = true;
		const std::string input = getNonEmptyString(prompt);

		for (size_t i = 0; i < input.length(); ++i) {
			if (!isdigit(input[i])) {
				std::cout << "Input must contain digits only.\n";
				valid = false;
				break;
			}
		}

		if (valid)
			number = atoi(input.c_str());
	} while (!valid);
	return number;
}

void PhoneBook::addContact(const Contact &contact) {
	if (contactCount == 8) {
		for (int i = 1; i < 8; i++) {
			contacts[i - 1] = contacts[i];
		}
		contacts[7] = contact;
	} else {
		contacts[contactCount++] = contact;
	}
}

void PhoneBook::addContactPrompt() {
	const std::string firstName = getNonEmptyString("Enter first name: ");
	const std::string lastName = getNonEmptyString("Enter last name: ");
	const std::string nickname = getNonEmptyString("Enter nickname: ");
	const int phoneNumber = getNonEmptyInteger("Enter phone number: ");
	const std::string darkestSecret = getNonEmptyString(
		"Enter darkest secret: ");

	const Contact newContact(firstName, lastName, nickname, phoneNumber,
							darkestSecret);
	addContact(newContact);
}

void displayTenChars(const std::string &str) {
	if (str.length() > 10) {
		std::cout << str.substr(0, 9) << ".";
	} else {
		std::cout << std::setw(10) << str;
	}
}

void PhoneBook::displayContacts() const {
	std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
	for (int i = 0; i < contactCount; i++) {
		std::cout << "|";
		std::cout << std::setw(10) << i;
		std::cout << "|";
		displayTenChars(contacts[i].getFirstName());
		std::cout << "|";
		displayTenChars(contacts[i].getLastName());
		std::cout << "|";
		displayTenChars(contacts[i].getNickname());
		std::cout << "|" << std::endl;
	}
}

void PhoneBook::displayContact(int index) const {
	if (index < 0 || index >= contactCount) {
		std::cout << "There are only " << contactCount <<
			" contacts in the phonebook." << std::endl;
		return;
	}
	const Contact &contact = contacts[index];
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}

void PhoneBook::searchContact() const {
	if (contactCount == 0) {
		std::cout << "The phonebook is empty." << std::endl;
		return;
	}

	displayContacts();

	int index;
	bool valid = false;

	while (!valid) {
		index = getNonEmptyInteger("Index of entry to display: ");
		if (index < 0 || index >= contactCount) {
			std::cout << "There are only " << contactCount <<
				" contacts in the phonebook." << std::endl;
		} else {
			valid = true;
		}
	}

	displayContact(index);
}
