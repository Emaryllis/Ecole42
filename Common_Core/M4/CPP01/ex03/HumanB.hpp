#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB {
public:
	explicit HumanB(const std::string &name);
	void attack() const;
	void setWeapon(Weapon &weapon);

private:
	std::string name;
	Weapon *weapon;
};

#endif
