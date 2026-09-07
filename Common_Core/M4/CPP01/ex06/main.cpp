#include "Harl.hpp"
#include <iostream>

int find_level(const std::string &level) {
	const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	for (int i = 0; i < 4; i++) {
		if (level.compare(levels[i]) == 0)
			return i + 1;
	}
	return -1;
}

void filter(const std::string &level, const Harl &harl) {
	switch (find_level(level)) {
	case 1:
		harl.complain("DEBUG"); // fall through
	case 2:
		harl.complain("INFO"); // fall through
	case 3:
		harl.complain("WARNING"); // fall through
	case 4:
		harl.complain("ERROR");
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]" <<
			std::endl;
	}
}

int main(int argc, char **argv) {
	const Harl harl;
	if (argc != 2) {
		filter("NONEXISTENT", harl);
		return 1;
	}
	filter(argv[1], harl);
	return 0;
}
