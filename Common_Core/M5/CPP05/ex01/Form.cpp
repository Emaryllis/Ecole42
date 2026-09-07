#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: _name("Default Form"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << "Form Default constructor called for" << _name << std::endl;
}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	std::cout << "Form Parameterized constructor called for" << _name << std::endl;
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute) {
	std::cout << "Form Copy constructor called for" << _name << std::endl;
}

Form &Form::operator=(const Form &other) {
	if (this != &other) {
		_isSigned = other._isSigned;
	}
	std::cout << "Form Copy assignment operator called for " << _name << std::endl;
	return *this;
}

Form::~Form() {
	std::cout << "Form Destructor called for " << _name << std::endl;
}

const std::string &Form::getName() const {
	return _name;
}

bool Form::getIsSigned() const {
	return _isSigned;
}

int Form::getGradeToSign() const {
	return _gradeToSign;
}

int Form::getGradeToExecute() const {
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw() {
	return "Form grade requirement is too high! (Highest possible grade is 1)";
}

const char *Form::GradeTooLowException::what() const throw() {
	return "Form grade requirement is too low or bureaucrat grade is too low!";
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
	os << "Form \"" << form.getName() << "\": "
		<< "Signed = " << (form.getIsSigned() ? "Yes" : "No")
		<< ", Grade Required to Sign = " << form.getGradeToSign()
		<< ", Grade Required to Execute = " << form.getGradeToExecute() << ".";
	return os;
}