#include "Zombie.hpp"

int main() {
	const Zombie zombie1("Zombie1");
	zombie1.announce();

	randomChump("Zombie2");

	const Zombie zombie3("Zombie3");

	return 0;
}
