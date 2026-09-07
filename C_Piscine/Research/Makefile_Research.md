## Makefile Variables
<details>
<summary>View More</summary>
<br/>
In Makefiles, the `:=` operator is used for simple variable assignment, also known as "simply expanded variables." This is in contrast to the `=` operator, which is used for recursively expanded variables. The key difference between these two lies in when the variable's value is expanded.

### Simply Expanded Variables (`:=`)

When you use `:=` to assign a value to a variable, the value is expanded at the time of assignment. This means that if the value of the variable contains references to other variables, those references are expanded immediately. This is useful when you want to ensure that the value of the variable is fully resolved at the time of assignment, without waiting for the variable to be used later in the Makefile.

For example:

```makefile
VERSION := 1.0
PROGRAM := myprogram-$(VERSION)
```

In this case, `PROGRAM` is assigned the value `myprogram-1.0` immediately, because `VERSION` is expanded at the time of assignment.

### Recursively Expanded Variables (`=`)

On the other hand, when you use `=` to assign a value to a variable, the value is expanded each time the variable is used, not when it is assigned. This means that if the value of the variable contains references to other variables, those references are expanded at the time of use. This is useful when the value of a variable depends on other variables that might change during the execution of the Makefile.

For example:

```makefile
VERSION = 1.0
PROGRAM = myprogram-$(VERSION)
```

In this case, `PROGRAM` is not assigned the value `myprogram-1.0` immediately. Instead, each time `PROGRAM` is used, `VERSION` is expanded to its current value, and `PROGRAM` is assigned the value `myprogram-1.0` at that moment.

### Choosing Between `:=` and `=`

The choice between using `:=` and `=` depends on the specific needs of your Makefile. If you need the value of a variable to be fully resolved at the time of assignment, use `:=`. If the value of a variable might depend on other variables that could change during the execution of the Makefile, use `=`.

In summary, simply expanded variables in Makefiles are those assigned with `:=`, where the value is expanded immediately at the time of assignment. This is in contrast to recursively expanded variables, which are assigned with `=` and are expanded each time they are used.

### Can't you just use `:=` for everything?

Using `:=` (simply expanded variables) every single time in a Makefile might seem like a straightforward approach, but it's not always the best practice for several reasons:

1. **Late Expansion**: One of the key benefits of using `=` (recursively expanded variables) is that it allows for late expansion. This means that the value of a variable can be determined based on the current state of other variables at the time it is used, not when it is defined. This is particularly useful in scenarios where the value of a variable depends on the outcome of commands or other variables that might change during the execution of the Makefile.

2. **Performance**: Simply expanded variables are expanded at the time of assignment, which can lead to unnecessary computation if the value of the variable does not actually depend on other variables. This can potentially slow down the execution of your Makefile, especially if you have a large number of variables or complex expressions.

3. **Flexibility**: Using `=` provides more flexibility in how variables are expanded and used. It allows for more dynamic behavior in your Makefiles, which can be beneficial in complex projects where the build environment or configuration might change.

4. **Compatibility**: Some Makefiles or Makefile conventions might rely on the recursive expansion behavior of `=`. Changing all assignments to `:=` could potentially break compatibility with these conventions or with other Makefiles that you might be including or extending.

In summary, while using `:=` every single time might seem like a simpler approach, it's important to consider the specific needs of your Makefile and the potential implications of late expansion, performance, flexibility, and compatibility. In many cases, a mix of `:=` and `=` will provide the best balance between simplicity and flexibility for your project.
</details>

## Rules, Sub-rules, and Dependencies
<details>
<summary>View More</summary>
<br/>
Understanding rules and sub-rules in Makefiles can indeed be confusing at first, but once you grasp the basics, they become a powerful tool for managing build processes. Let's break down these concepts to clarify them.

### Rules in Makefiles

A rule in a Makefile defines a target, its dependencies, and the commands to execute to update the target. The basic syntax of a rule is:

```makefile
target: dependencies
    command1
    command2
    ...
```

- **Target**: This is the file that the rule is supposed to create or update. It can also be a phony target (a target that doesn't correspond to a file).
- **Dependencies**: These are files that the target depends on. If any of these files are newer than the target, the commands for the target will be executed.
- **Commands**: These are the shell commands that will be executed to update the target. They are executed in the order they appear.

### Sub-rules

Sub-rules, also known as pattern rules, allow you to define a rule that applies to multiple targets that match a certain pattern. This is useful for reducing redundancy in your Makefile, especially when you have many similar targets.

The syntax for a pattern rule is:

```makefile
%.o: %.c
    command1
    command2
    ...
```

In this example, `%.o` is the target pattern, and `%.c` is the dependency pattern. This rule applies to any `.o` file that depends on a corresponding `.c` file. The `%` character is a wildcard that matches any string.

### Example

Let's consider a simple Makefile for a C project:

```makefile
CC = gcc
CFLAGS = -Wall -g

# Rule for the final executable
myprogram: main.o utils.o
    $(CC) $(CFLAGS) -o myprogram main.o utils.o

# Pattern rule for compiling .c files to .o files
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Phony target for cleaning up
.PHONY: clean
clean:
    rm -f *.o myprogram
```

In this Makefile:

- The `myprogram` rule specifies how to build the `myprogram` executable from `main.o` and `utils.o`.
- The `%.o: %.c` pattern rule specifies how to compile `.c` files into `.o` files. The `$<` variable represents the first dependency (the `.c` file), and the `$@` variable represents the target (the `.o` file).
- The `.PHONY: clean` rule is a special case. It's used to define a target that doesn't correspond to a file. In this case, it's used to clean up the build artifacts.

When you run `make myprogram` in the context of the Makefile example provided, it specifies that `myprogram` depends on `main.o` and `utils.o`. This means that `make` will first check if `main.o` and `utils.o` exist and if they are newer than `myprogram`. If either `main.o` or `utils.o` does not exist, or if they are newer than `myprogram`, `make` will execute the commands associated with the rule for `myprogram` to update it.

Here's a step-by-step breakdown of what happens when you run `make myprogram`:

1. **Check Dependencies**: `make` looks at the dependencies of `myprogram`, which are `main.o` and `utils.o`.
2. **Check Timestamps**: For each dependency, `make` checks if the dependency file exists and if it is newer than the target file (`myprogram`).
3. **Compile Dependencies**: If `main.o` or `utils.o` does not exist, or if they are newer than `myprogram`, `make` will execute the commands associated with the pattern rule `%.o: %.c` to compile `main.c` and `utils.c` into `main.o` and `utils.o`.
4. **Link Executable**: After `main.o` and `utils.o` are up to date, `make` will execute the commands associated with the `myprogram` rule to link `main.o` and `utils.o` into the executable `myprogram`.

This process ensures that `myprogram` is always up to date with the latest versions of its dependencies. If you modify `main.c` or `utils.c` and then run `make myprogram`, `make` will automatically recompile the changed `.c` files and relink the executable, ensuring that `myprogram` reflects the latest changes.


### Conclusion

Rules and sub-rules in Makefiles are powerful tools for managing build processes. Rules define how to build specific targets, while sub-rules (pattern rules) allow you to define rules that apply to multiple targets. Understanding these concepts is key to writing efficient and maintainable Makefiles.
</details>

## Automatic Variables
<details>
<summary>View More</summary>
<br/>
In the context of Makefiles, "automatic variables" are special variables that `make` automatically sets for each rule. These variables are predefined by `make` and can be used within the recipe (the commands that follow the rule) to refer to various parts of the rule itself. They are particularly useful for writing generic rules that can be applied to multiple targets without hardcoding specific filenames.

Here are some of the most commonly used automatic variables in Makefiles:

- `$@`: Represents the target of the rule. For example, if the rule is `foo.o: foo.c`, then `$@` would be `foo.o`.
- `$<`: Represents the first prerequisite of the rule. In the same example, `$<` would be `foo.c`.
- `$^`: Represents all prerequisites of the rule. In the example, `$^` would be `foo.c`.
- `$+`: Similar to `$^`, but it includes duplicate prerequisites only once.
- `$*`: Represents the stem with which an implicit rule matches. For example, in a pattern rule like `%.o: %.c`, if the target is `foo.o`, then `$*` would be `foo`.
- `$?`: Represents all prerequisites that are newer than the target.

These automatic variables are very powerful because they allow you to write rules that are more generic and can be applied to multiple targets without modification. This is particularly useful in large projects where you might have many source files that need to be compiled into object files, or where you have multiple targets that depend on the same set of source files.

For example, consider a rule for compiling C source files into object files:

```makefile
%.o: %.c
    gcc -c $< -o $@
```

In this rule:
- `$<` is the name of the `.c` file that is being compiled.
- `$@` is the name of the `.o` file that is being generated.

This rule can be applied to any `.c` file to compile it into a corresponding `.o` file, making it very flexible and reducing the need for repetitive code in the Makefile.
</details>

## Pattern Substitution V.S. Substitution References
<details>
<summary>View More</summary>
<br/>

### `$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))`

- **`patsubst`**: This is a `make` function that performs pattern substitution. It takes three arguments: a pattern to match, a pattern to replace it with, and a text (or list of texts) to perform the substitution on.
- **`$(SRC_DIR)/%.c`**: This is the pattern to match. It matches any `.c` file in the `$(SRC_DIR)` directory.
- **`$(SRC_DIR)/%.o`**: This is the pattern to replace the matched pattern with. It specifies that the matched `.c` file should be replaced with a corresponding `.o` file in the same directory.
- **`$(SRCS)`**: This is the list of source files to perform the substitution on. It's expected to be a list of `.c` files.

### `$(SRCS:.c=.o)`

- **`$(SRCS:.c=.o)`**: This is a `make` substitution reference. It's a simpler way to perform pattern substitution directly on a variable. It replaces the `.c` extension with `.o` for each item in the `$(SRCS)` list.

### Comparison

- **Simplicity**: `$(SRCS:.c=.o)` is simpler and more straightforward for this specific task of changing file extensions.
- **Flexibility**: `$(patsubst ...)` is more flexible and can be used for more complex pattern substitutions, not just changing file extensions.
- **Context**: `$(patsubst ...)` allows you to specify the directory (`$(SRC_DIR)`) explicitly, which can be useful if your source files are not all in the same directory or if you want to ensure that the transformation is applied only to files in a specific directory.

### Conclusion

Both methods are valid for transforming a list of `.c` files into a list of `.o` files in a Makefile. The choice between them depends on your specific needs and preferences. If you're only changing file extensions and your source files are all in the same directory, `$(SRCS:.c=.o)` is likely the simpler and more straightforward choice. If you need more flexibility or are working with files in different directories, `$(patsubst ...)` might be more appropriate.
</details>
