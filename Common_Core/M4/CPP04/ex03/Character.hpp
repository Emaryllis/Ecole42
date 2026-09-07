#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include "ICharacter.hpp"

class Character : public ICharacter {
public:
	Character();
	Character(std::string const& name);
	Character(Character const& other);
	Character& operator=(Character const& other);
	~Character();

	std::string const& getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
private:
	std::string name;
	AMateria* inventory[4];

	void clearInventory();
	void copyInventory(Character const& other);
};

#endif
