#ifndef SIGSEGV_HPP
# define SIGSEGV_HPP

#include <csignal>
#include <cstdlib>
#include <iostream>
#include "color.hpp"

using namespace std;

void sigsegv(int signal);

#endif