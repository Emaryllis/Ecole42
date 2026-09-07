#include "Zombie.hpp"

int main() {
	const Zombie *horde = zombieHorde(10, "Zombies");
	for (int i = 0; i < 10; i++) {
		horde[i].announce();
	}
	delete[] horde;

	return 0;
}
