#include "HumanA.hpp"
#include "HumanB.hpp"

int main() {
	Weapon club("crude spiked club");

	HumanA bob("bob", club);
	bob.attack();
	club.setType("some other type of club");
	bob.attack();

	HumanB jim("Jim");
	jim.setWeapon(club);
	jim.attack();
	club.setType("some other type of club");
	jim.attack();

	return 0;
}
