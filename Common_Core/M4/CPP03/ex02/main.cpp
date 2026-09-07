#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main() {
	FragTrap fragtrap("Fragtrap1");
	fragtrap.attack("Dummy1");
	fragtrap.takeDamage(25);
	fragtrap.beRepaired(10);
	fragtrap.highFivesGuys();

	FragTrap copy(fragtrap);
	copy.attack("Dummy2");

	FragTrap assigned("Fragtrap2");
	assigned = fragtrap;
	assigned.takeDamage(150);
	assigned.attack("Dummy2");
	assigned.beRepaired(5);

	return 0;
}
