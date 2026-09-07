#include <iostream>
#include <cctype>

int main(int c, char **v) {
	if (c == 1) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	for (int i = 1; i < c; i++) {
		for (int j = 0; v[i][j] != '\0'; j++) {
			std::cout << static_cast<char>(
				std::toupper(static_cast<unsigned char>(v[i][j]))
			);
		}
	}
	std::cout << '\n';
	return 0;
}
