#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("Shrubbery Creation Form", 145, 137), _target("default_target") {
	std::cout << "ShrubberyCreationForm Default constructor called for " << this->getName() << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("Shrubbery Creation Form", 145, 137), _target(target) {
	std::cout << "ShrubberyCreationForm Parameterized constructor called for " << this->getName() << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other), _target(other._target) {
	std::cout << "ShrubberyCreationForm Copy constructor called for " << this->getName() << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	std::cout << "ShrubberyCreationForm Copy assignment operator called for " << this->getName() << std::endl;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "ShrubberyCreationForm Destructor called for " << this->getName() << std::endl;
}

const std::string &ShrubberyCreationForm::getTarget() const {
	return _target;
}

void ShrubberyCreationForm::executeAction() const {
	std::ofstream outfile((_target + "_shrubbery").c_str());
	if (!outfile.is_open()) {
		std::cerr << "Error: Could not create output file." << std::endl;
		return;
	}

	outfile << "       _-_\n"
		<< "    /~~   ~\\\n"
		<< " /~~         ~~\\\n"
		<< "{               }\n"
		<< " \\  _-     -_  /\n"
		<< "   ~  \\\\ //  ~\n"
		<< "_- -   | | _- _\n"
		<< "  _ -  | |   -_\n"
		<< "      // \\\\\n";
	outfile.close();
}