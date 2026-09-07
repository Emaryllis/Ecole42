#include "Contact.hpp"

Contact::Contact() : phoneNumber(0) {
}

Contact::Contact(const std::string &firstName, const std::string &lastName,
				const std::string &nickname,
				int phoneNumber,
				const std::string &darkestSecret) : firstName(firstName),
													lastName(lastName),
													nickname(nickname),
													phoneNumber(phoneNumber),
													darkestSecret(
														darkestSecret) {
}

const std::string &Contact::getFirstName() const {
	return firstName;
}

const std::string &Contact::getLastName() const {
	return lastName;
}

const std::string &Contact::getNickname() const {
	return nickname;
}

int Contact::getPhoneNumber() const {
	return phoneNumber;
}

const std::string &Contact::getDarkestSecret() const {
	return darkestSecret;
}
