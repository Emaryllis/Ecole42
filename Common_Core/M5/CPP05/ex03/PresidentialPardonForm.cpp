#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("Presidential Pardon Form", 25, 5), _target("default_target") {
	std::cout << "PresidentialPardonForm Default constructor called for " << this->getName() << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm("Presidential Pardon Form", 25, 5), _target(target) {
	std::cout << "PresidentialPardonForm Parameterized constructor called for " << this->getName() << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
	: AForm(other), _target(other._target) {
	std::cout << "PresidentialPardonForm Copy constructor called for " << this->getName() << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	std::cout << "PresidentialPardonForm Copy assignment operator called for " << this->getName() << std::endl;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "PresidentialPardonForm Destructor called for " << this->getName() << std::endl;
}

const std::string &PresidentialPardonForm::getTarget() const {
	return _target;
}

void PresidentialPardonForm::executeAction() const {
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}