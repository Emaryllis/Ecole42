#ifndef SIGSEGV_HPP
# define SIGSEGV_HPP

# include <csignal>
# include <iostream>
# include <stdlib.h>
# include "color.hpp"

using namespace std;

void sigsegv(int signal);

#endif