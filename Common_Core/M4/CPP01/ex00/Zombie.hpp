#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	explicit Zombie(const std::string &name);
	void announce() const;
	~Zombie();

private:
	std::string name;
};

Zombie *newZombie(const std::string &name);
void randomChump(const std::string &name);

#endif
