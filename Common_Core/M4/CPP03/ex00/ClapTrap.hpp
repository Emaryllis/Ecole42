#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
public:
	ClapTrap();
	ClapTrap(const std::string &name);
	virtual ~ClapTrap();
	ClapTrap(const ClapTrap &obj);
	ClapTrap &operator=(const ClapTrap& other);

	virtual void attack(const std::string &target);
	virtual void takeDamage(unsigned int amount);
	virtual void beRepaired(unsigned int amount);

private:
	std::string name;
	unsigned int hitPoints;
	unsigned int energyPoints;
	int attackDamage;
};

#endif
