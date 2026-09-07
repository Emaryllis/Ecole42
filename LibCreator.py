import sys, os, glob
from io import StringIO

COLUMN_LIMIT = 80 # Norm v4 column limit
TAB_WIDTH = 8

def printHelp():
    print("""Usage: python LibCreator.py [options] <src_pattern>

Options:
  -f               Force overwrite of existing Makefile
  -l <lib_name>    Set custom library name (required)
  -h, --help       Show this help message and exit

Examples:
  python LibCreator.py -l libft *.c
  python LibCreator.py -f -l libft *.c
  python LibCreator.py -l libft *.c utils/*.c
""")

def writeVariables(buf, libName):
    buf.write(f"""# Variables
NAME = {libName}.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
""")

def writeSources(buf, patterns):
    source = "SRC = "
    buf.write(source)
    lineLen = len(source)
    first = True
    for pattern in patterns:
        # Change to glob.glob(pattern, recursive=True) if requires matching of deeply nested files
        for filePath in glob.glob(pattern):
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

def writePatterns(buf):
    buf.write("""\n# Patterns
%.o: %.c
\t$(CC) $(CFLAGS) -c $< -o $@
""")

def writeRules(buf):
    buf.write("""\n# Rules
all: $(NAME)

$(NAME): $(OBJ)
\t$(AR) $@ $^

clean:
\trm -f $(OBJ)

fclean: clean
\trm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re""")

def createMakefile(patterns, libName):
    buf = StringIO()
    writeVariables(buf, libName)
    writeSources(buf, patterns)
    writePatterns(buf)
    writeRules(buf)
    with open("Makefile", "w") as file:
        file.write(buf.getvalue())

if __name__ == "__main__":
    args, force, libName, i = sys.argv[1:], False, None, 0
    while i < len(args):
        match args[i]:
            case "-f":
                force, i = True, i + 1
            case "-l":
                i += 1
                if i >= len(args): sys.exit("Error: -l requires <lib_name>")
                libName, i = args[i], i + 1
            case "-h" | "--help":
                printHelp()
                sys.exit(0)
            case _:
                break # Stop parsing flags
    patterns = args[i:]
    if not libName: sys.exit("Error: missing required -l <lib_name>")
    if not patterns: sys.exit("Error: no source pattern provided. Use -h for help.")
    if os.path.exists("Makefile") and not force:
        sys.exit("Error: Makefile already exists. Use -f to overwrite.")
    createMakefile(patterns, libName)
    print(f"Makefile for {libName}.a created successfully!")

