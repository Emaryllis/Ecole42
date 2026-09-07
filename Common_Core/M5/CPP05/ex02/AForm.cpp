#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): _name("Default AForm"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << "AForm Default constructor called for" << _name << std::endl;
}

AForm::AForm(const std::string &name, const int gradeToSign, const int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	std::cout << "AForm Parameterized constructor called for" << _name << std::endl;
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
	: _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute) {
	std::cout << "AForm Copy constructor called for" << _name << std::endl;
}

AForm &AForm::operator=(const AForm &other) {
	if (this != &other) {
		_isSigned = other._isSigned;
	}
	std::cout << "AForm Copy assignment operator called for " << _name << std::endl;
	return *this;
}

AForm::~AForm() {
	std::cout << "AForm Destructor called for " << _name << std::endl;
}

const std::string &AForm::getName() const {
	return _name;
}

bool AForm::getIsSigned() const {
	return _isSigned;
}

int AForm::getGradeToSign() const {
	return _gradeToSign;
}

int AForm::getGradeToExecute() const {
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(const Bureaucrat &executor) const {
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooLowException();
	executeAction();
}

const char *AForm::GradeTooHighException::what() const throw() {
	return "grade requirement is too high!";
}

const char *AForm::GradeTooLowException::what() const throw() {
	return "grade is too low!";
}

const char *AForm::FormNotSignedException::what() const throw() {
	return "form is not signed!";
}

std::ostream &operator<<(std::ostream &os, const AForm &form) {
	os << "Form \"" << form.getName() << "\": "
		<< "Signed = " << (form.getIsSigned() ? "Yes" : "No")
		<< ", Grade Required to Sign = " << form.getGradeToSign()
		<< ", Grade Required to Execute = " << form.getGradeToExecute() << ".";
	return os;
}