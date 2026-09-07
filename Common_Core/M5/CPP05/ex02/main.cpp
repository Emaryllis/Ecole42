#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>
#include <cstdlib>

int main() {
	std::srand(std::time(NULL));

	std::cout << "=== 1. Testing Unsigned Execution Failure ===" << std::endl;
	Bureaucrat president("President", 1);
	ShrubberyCreationForm shrub("backyard");

	president.executeForm(shrub);

	std::cout << "\n=== 2. Testing ShrubberyCreationForm ===" << std::endl;
	Bureaucrat gardener("Gardener", 137);
	gardener.signForm(shrub);
	gardener.executeForm(shrub);

	std::cout << "\n=== 3. Testing RobotomyRequestForm ===" << std::endl;
	Bureaucrat engineer("Engineer", 45);
	RobotomyRequestForm robo("Bender");
	engineer.signForm(robo);
	engineer.executeForm(robo);
	engineer.executeForm(robo);
	engineer.executeForm(robo);

	std::cout << "\n=== 4. Testing PresidentialPardonForm ===" << std::endl;
	Bureaucrat boss("Zaphod Assistant", 5);
	PresidentialPardonForm pardon("Arthur Dent");
	boss.signForm(pardon);
	boss.executeForm(pardon);

	std::cout << "\n=== 5. Testing Insufficient Grade to Execute ===" << std::endl;
	Bureaucrat intern("Intern", 140);
	PresidentialPardonForm highLevelPardon("Ford Prefect");
	intern.signForm(highLevelPardon);
	intern.executeForm(highLevelPardon);

	return 0;
}