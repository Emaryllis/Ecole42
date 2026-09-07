#include "Zombie.hpp"

void randomChump(const std::string &name) {
	const Zombie zombie(name);
	zombie.announce();
}
