#include "Bureaucrat.hpp"

int main() {
    std::cout << "=== 1. Valid Bureaucrat Tests ===" << std::endl;
    try {
        Bureaucrat john("John", 3);
        std::cout << john << std::endl;

        john.incrementGrade();
        std::cout << "After increment: " << john << std::endl;

        john.decrementGrade();
        std::cout << "After decrement: " << john << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== 2. Constructor Exception Tests (Too High) ===" << std::endl;
    try {
        Bureaucrat boss("Too High Boss", 0);
    }
    catch (const std::exception &e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== 3. Constructor Exception Tests (Too Low) ===" << std::endl;
    try {
        Bureaucrat intern("Too Low Intern", 151);
    }
    catch (const std::exception &e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== 4. Boundary Increment Exception Test ===" << std::endl;
    try {
        Bureaucrat top("Top Official", 1);
        std::cout << top << std::endl;
        std::cout << "Attempting to increment grade 1..." << std::endl;
        top.incrementGrade();
    }
    catch (const std::exception &e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== 5. Boundary Decrement Exception Test ===" << std::endl;
    try {
        Bureaucrat low("Low Official", 150);
        std::cout << low << std::endl;
        std::cout << "Attempting to decrement grade 150..." << std::endl;
        low.decrementGrade();
    }
    catch (const std::exception &e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    return 0;
}