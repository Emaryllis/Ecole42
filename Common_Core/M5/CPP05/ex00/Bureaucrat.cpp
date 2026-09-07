#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): _name("Default Bureaucrat"), _grade(150) {
	std::cout << "Bureaucrat Default constructor called for" << _name << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, const int grade): _name(name) {
	std::cout << "Bureaucrat Parameterized constructor called for" << _name << std::endl;
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: _name(other._name), _grade(other._grade) {
	std::cout << "Bureaucrat Copy constructor called for" << _name << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	if (this != &other) {
		_grade = other._grade;
	}
	std::cout << "Bureaucrat Copy assignment operator called for " << _name << std::endl;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "Bureaucrat Destructor called for " << _name << std::endl;
}

const std::string &Bureaucrat::getName() const {
	return _name;
}

int Bureaucrat::getGrade() const {
	return _grade;
}

void Bureaucrat::incrementGrade() {
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	_grade--;
}

void Bureaucrat::decrementGrade() {
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	_grade++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade is too high! (Highest possible grade is 1)";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade is too low! (Lowest possible grade is 150)";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}