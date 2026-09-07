#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria {
public:
	AMateria(std::string const& type);
	AMateria();
	AMateria(AMateria const& other);
	AMateria& operator=(AMateria const& other);
	virtual ~AMateria();

	std::string const& getType() const;
	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
protected:
	std::string type;
};

#endif
