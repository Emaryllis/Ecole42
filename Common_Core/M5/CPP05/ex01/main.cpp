#include "Form.hpp"

int main() {
	std::cout << "=== 1. Valid Form Construction & Insertion Operator ===" << std::endl;
	try {
		const Form taxForm("Tax Form 21B", 50, 25);
		std::cout << taxForm << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== 2. Invalid Form Construction (Too High) ===" << std::endl;
	try {
		Form highForm("High Form", 0, 100);
	} catch (const std::exception &e) {
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== 3. Invalid Form Construction (Too Low) ===" << std::endl;
	try {
		Form lowForm("Low Form", 100, 151);
	} catch (const std::exception &e) {
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== 4. Successful Form Signing ===" << std::endl;
	try {
		const Bureaucrat boss("Alice", 10);
		Form permit("Building Permit", 20, 10);

		std::cout << boss << std::endl;
		std::cout << permit << std::endl;

		boss.signForm(permit);
		std::cout << "After signing: " << permit << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== 5. Failed Form Signing (Grade Too Low) ===" << std::endl;
	try {
		const Bureaucrat intern("Bob", 100);
		Form topSecret("Classified Archive Access", 50, 10);

		std::cout << intern << std::endl;
		std::cout << topSecret << std::endl;

		intern.signForm(topSecret);
		std::cout << "After failed sign attempt: " << topSecret << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	return 0;
}