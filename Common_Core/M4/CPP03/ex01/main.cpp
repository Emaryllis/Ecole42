#include "ScavTrap.hpp"

int main()
{
	ScavTrap scavtrap1("ScavTrap");

	scavtrap1.attack("Dummy1");
	scavtrap1.takeDamage(42);
	scavtrap1.beRepaired(10);
	scavtrap1.guardGate();

	ScavTrap assigned("ScavTrap Assignment");
	assigned = scavtrap1;

	assigned.attack("Dummy2");
	assigned.takeDamage(120);
	assigned.attack("Dummy3");
	assigned.beRepaired(5);

	ScavTrap copy(scavtrap1);
	copy.attack("Dummy4");

	return 0;
}
