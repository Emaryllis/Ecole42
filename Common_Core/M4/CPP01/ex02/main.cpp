#include <string>
#include <iostream>

int main() {
	const std::string string = "HI THIS IS BRAIN";
	const std::string *stringPTR = &string;
	const std::string &stringREF = string;

	std::cout << "String: " << &string << std::endl;
	std::cout << "String Ptr: " << stringPTR << std::endl;
	std::cout << "String Ref: " << &stringREF << std::endl;

	std::cout << "Value: " << string << std::endl;
	std::cout << "Value Ptr: " << *stringPTR << std::endl;
	std::cout << "Value Ref: " << stringREF << std::endl;

	return 0;
}
