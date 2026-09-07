#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>

class AAnimal {
public:
    AAnimal();
    AAnimal(const std::string& type);
    AAnimal(const AAnimal& other);
    AAnimal& operator=(const AAnimal& other);
    virtual ~AAnimal();

    std::string getType() const;
    virtual void makeSound() const = 0;
protected:
	std::string type;
};
#endif
