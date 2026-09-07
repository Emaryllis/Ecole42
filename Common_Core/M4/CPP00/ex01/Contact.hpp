#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

class Contact {
public:
	Contact();
	Contact(const std::string &firstName, const std::string &lastName,
			const std::string &nickname, int phoneNumber,
			const std::string &darkestSecret);
	const std::string &getFirstName() const;
	const std::string &getLastName() const;
	const std::string &getNickname() const;
	int getPhoneNumber() const;
	const std::string &getDarkestSecret() const;

private:
	std::string firstName;
	std::string lastName;
	std::string nickname;
	int phoneNumber;
	std::string darkestSecret;
};
#endif
