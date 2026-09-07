#include "ClapTrap.hpp"

int main() {
	ClapTrap claptrap("ClapTrap");

	claptrap.attack("Target1");
	claptrap.takeDamage(3);
	claptrap.beRepaired(1);

	// More actions
	claptrap.attack("Target2");
	claptrap.takeDamage(100);
	claptrap.beRepaired(50);

	return 0;
}
