#include "DiamondTrap.hpp"
#include <iostream>

int main() {
	DiamondTrap diamondtrap("DiamondTrap1");
	diamondtrap.attack("Dummy1");
	diamondtrap.takeDamage(42);
	diamondtrap.beRepaired(10);
	diamondtrap.highFivesGuys();
	diamondtrap.guardGate();
	diamondtrap.whoAmI();

	DiamondTrap copy(diamondtrap);
	copy.whoAmI();

	DiamondTrap assigned("DiamondTrap2");
	assigned = diamondtrap;
	assigned.whoAmI();
	assigned.takeDamage(200);
	assigned.attack("Dummy2");

	return 0;
}
