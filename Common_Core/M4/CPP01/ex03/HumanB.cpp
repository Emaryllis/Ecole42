#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : name(name), weapon(NULL) {
}

void HumanB::attack() const {
	if (weapon == NULL) {
		std::cout << name << " attacks with their bare hands" << std::endl;
		return;
	}
	std::cout << name << " attacks with their " << weapon->getType() <<
		std::endl;
}

void HumanB::setWeapon(Weapon &newWeapon) {
	weapon = &newWeapon;
}
