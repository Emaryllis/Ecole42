# include "sigsegv.hpp"
# include <cstring>
# include <unistd.h>
# include "color.hpp"

# include <sys/wait.h>

extern int iTest;
extern bool showTest;
extern int pipeOut;
extern int stdOut;

void sigsegv(int signal)
{
	(void)signal;
	dup2(stdOut, 1);
	if (showTest)
		cout << FG_BLUE << "ft_printf: " << FG_LYELLOW << "[SIGSEGV]" << ENDL;
	else
		cout << FG_LYELLOW << iTest++ << ".SIGSEGV ";
	dup2(pipeOut, 1);
	exit(EXIT_SUCCESS);
}