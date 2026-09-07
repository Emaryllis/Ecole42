#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"

int main() {
	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1);

	std::cout << "\n=== 1. Valid Form Creation: Robotomy Request ===" << std::endl;
	AForm *formPtr = someRandomIntern.makeForm("robotomy request", "Bender");
	if (formPtr) {
		boss.signForm(*formPtr);
		boss.executeForm(*formPtr);
		delete formPtr;
	}

	std::cout << "\n=== 2. Valid Form Creation: Shrubbery Creation ===" << std::endl;
	formPtr = someRandomIntern.makeForm("shrubbery creation", "Home");
	if (formPtr) {
		boss.signForm(*formPtr);
		boss.executeForm(*formPtr);
		delete formPtr;
	}

	std::cout << "\n=== 3. Valid Form Creation: Presidential Pardon ===" << std::endl;
	formPtr = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
	if (formPtr) {
		boss.signForm(*formPtr);
		boss.executeForm(*formPtr);
		delete formPtr;
	}

	std::cout << "\n=== 4. Invalid Form Name ===" << std::endl;
	formPtr = someRandomIntern.makeForm("tax evasion request", "Corporate");
	if (formPtr) {
		delete formPtr;
	}

	std::cout << "\n=== Cleanup ===" << std::endl;
	return 0;
}