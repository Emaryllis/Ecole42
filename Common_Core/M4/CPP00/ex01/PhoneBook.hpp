#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook();

	std::string getNonEmptyString(const std::string &prompt) const;

	void addContact(const Contact &contact);
	void addContactPrompt();
	void displayContacts() const;
	void displayContact(int index) const;
	void searchContact() const;

private:
	Contact contacts[8];
	int contactCount;
	int getNonEmptyInteger(const std::string &prompt) const;
};

#endif
