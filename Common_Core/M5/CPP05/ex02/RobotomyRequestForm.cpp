#include <cstdlib>
#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("Robotomy Request Form", 72, 45), _target("default_target") {
	std::cout << "RobotomyRequestForm default constructor called for " << this->getName() << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("Robotomy Request Form", 72, 45), _target(target) {
	std::cout << "RobotomyRequestForm parameterized constructor called for " << this->getName() << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other), _target(other._target) {
	std::cout << "RobotomyRequestForm copy constructor called for " << this->getName() << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	std::cout << "RobotomyRequestForm copy assignment operator called for " << this->getName() << std::endl;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "RobotomyRequestForm destructor called for " << this->getName() << std::endl;
}

const std::string &RobotomyRequestForm::getTarget() const {
	return _target;
}

void RobotomyRequestForm::executeAction() const {
	std::cout << "* VRRRRRRRRR... DRILLING NOISES *" << std::endl;
	if (std::rand() % 2 == 0) {
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	} else {
		std::cout << "Robotomy on " << _target << " failed." << std::endl;
	}
}