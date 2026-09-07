#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
public:
	void complain(const std::string &level) const;

private:
	void debug() const;
	void info() const;
	void warning() const;
	void error() const;
};

#endif
