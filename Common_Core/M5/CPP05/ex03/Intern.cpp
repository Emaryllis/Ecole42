#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"

Intern::Intern() {
	std::cout << "Intern Default constructor called" << std::endl;
}

Intern::Intern(const Intern &other) {
	(void)other;
	std::cout << "Intern Copy constructor called" << std::endl;
}

Intern &Intern::operator=(const Intern &other) {
	(void)other;
	std::cout << "Intern Copy assignment operator called" << std::endl;
	return *this;
}

Intern::~Intern() {
	std::cout << "Intern Destructor called" << std::endl;
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target) {
	const std::string knownForms[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	int formIndex = -1;
	for (int i = 0; i < 3; i++) {
		if (formName == knownForms[i]) {
			formIndex = i;
			break;
		}
	}

	switch (formIndex) {
		case 0:
			std::cout << "Intern creates Shrubbery Creation Form" << std::endl;
			return new ShrubberyCreationForm(target);
		case 1:
			std::cout << "Intern creates Robotomy Request Form" << std::endl;
			return new RobotomyRequestForm(target);
		case 2:
			std::cout << "Intern creates Presidential Pardon Form" << std::endl;
			return new PresidentialPardonForm(target);
		default:
			std::cerr << "Error: Intern cannot create form \"" << formName
				<< "\" because it does not exist." << std::endl;
			return NULL;
	}
}