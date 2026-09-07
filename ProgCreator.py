import sys, os, glob
from io import StringIO

COLUMN_LIMIT = 80 # Norm v4 column limit
TAB_WIDTH = 8

def printHelp():
    print("""Usage: python ProgCreator.py [options] <src_pattern>

Options:
  -f               Force overwrite of existing Makefile
  -l <lib_name>    Set custom library name (required)
  -h, --help       Show this help message and exit
  -r               Enable recursive globbing for source patterns

Examples:
  python ProgCreator.py -l pipex *.c
  python ProgCreator.py -f -l pipex *.c
  python ProgCreator.py -l pipex *.c utils/*.c
  python ProgCreator.py -l pipex -r src/**/*.c
  python ProgCreator.py -l pipex -r *.c **/*.c
""")

def writeVariables(buf, progName):
    buf.write(f"""# Variables
NAME = {progName}
CC = cc
CFLAGS = -Wall -Wextra -Werror
""")

def writeSources(buf, patterns, recursive):
    source = "SRC = "
    buf.write(source)
    lineLen = len(source)
    first = True
    for pattern in patterns:
        for filePath in glob.glob(pattern, recursive=recursive):
            if os.path.isfile(filePath):
                rel = os.path.relpath(filePath)
                if lineLen + len(rel) >= COLUMN_LIMIT:
                    buf.write(" \\\n\t")
                    lineLen = TAB_WIDTH
                elif not first:
                    buf.write(" ")
                    lineLen += 1 # Space character length
                buf.write(rel)
                lineLen += len(rel)
                first = False

    buf.write("\nOBJ = $(SRC:.c=.o)\n")

def writeRules(buf):
    buf.write("""\n# Rules
all: $(NAME)

$(NAME): $(OBJ)
\t$(CC) $(CFLAGS) -o $@ $^

clean:
\trm -f $(OBJ)

fclean: clean
\trm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re""")

def createMakefile(patterns, libName, recursive):
    buf = StringIO()
    writeVariables(buf, libName)
    writeSources(buf, patterns, recursive)
    writeRules(buf)
    with open("Makefile", "w") as file:
        file.write(buf.getvalue())

if __name__ == "__main__":
    args, force, libName, i, recursive = sys.argv[1:], False, None, 0, False
    while i < len(args):
        match args[i]:
            case "-h" | "--help":
                printHelp()
                sys.exit(0)
            case "-f":
                force, i = True, i + 1
            case "-l":
                i += 1
                if i >= len(args): sys.exit("Error: -l requires <prog_name>")
                libName, i = args[i], i + 1
            case "-r":
                recursive, i = True, i + 1
            case _:
                break # Stop parsing flags
    patterns = args[i:]
    if not libName: sys.exit("Error: missing required -l <prog_name>")
    if not patterns: sys.exit("Error: no source pattern provided. Use -h for help.")
    if os.path.exists("Makefile") and not force:
        sys.exit("Error: Makefile already exists. Use -f to overwrite.")
    createMakefile(patterns, libName, recursive)
    print(f"Makefile for {libName} created successfully!")
