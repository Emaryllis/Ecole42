#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	explicit Zombie(const std::string &name);
	void announce() const;
	void setName(const std::string &zombieName);
	~Zombie();

private:
	std::string name;
};

Zombie *zombieHorde(int N, const std::string &name);

#endif
