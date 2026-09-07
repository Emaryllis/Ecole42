# Exam03 Notes

## Get Next Line
- Imports required: stdlib.h, unistd.h
### Main problems in old version
1. Didn't update temp pointer; infinite loop.
2. Wrong return logic (returned early, not looping).
3. Did not handle read return value correctly (!= instead of <= 0>).
4. Did not shift buffer after extracting newline.
5. Failed to protect memory when appending fails.

### Things to change
1. **Always search for newline in static buffer (**`temp = ft_strchr(b, '\n')`**)**
2. **If found, append to ret up to newline (temp - b + 1) and move the contents after the newline back to the buffer.**<br /> **Note:** Remember to free ret and return NULL if append fails
3. **If no newline, append whole buffer to ret (**`str_append_str(&ret, b)`**)**<br />**Note:** Remember return NULL if append fails
4. **Read into buffer exactly BUFFER_SIZE (**`read_ret = read(fd, b, BUFFER_SIZE)`**)**
5. **If read returns <= 0, set buffer to empty string** `b[0] = '\0'`.<br/>**If** `ret && *ret`**, return ret. Else, free ret and return NULL**
6. **Null-terminate buffer after read (**`b[read_ret] = '\0'`**)**

### ft_strchr
**Problem:** Crashed when s was NULL or when searching past end.

**Fix:**
- Add `if (!s) return NULL`
- Loop until `s[i] == '\0'`. Return pointer only when match is found.<br/>**Why:** Prevent invalid reads when static buffer is empty.

### ft_memcpy
**Problem:** Old loop skipped copying index 0; size_t wraparound.

**Fix:**
- Use normal decrementing loop (`while (n > 0) { n--; dest[n] = src[n]; }`)

### ft_strlen

- **Problem:** Incremented pointer directly; no NULL check.

**Fix:**
- Add `if (!s) return 0;`
- Use index counter instead of pointer arithmetic.

### ft_memmove
**Problems:**
- Self-recursive call caused infinite recursion.
- No check for n == 0.
- Incorrect logic for overlapping regions.
- Could call ft_strlen on NULL.

**Fix:**
- If src == dest or n == 0 → return dest.
- If dest < src → forward copy.
- Else → backward copy.<br/>**Why:** Correct handling of overlapping memory.

### str_append_mem
**Problem:** Assumed memcpy handles NULL; failed when s1 == NULL.

**Fix:**
- Compute `size1 = ft_strlen(*s1)` safely.
- Allocate new buffer for size1 + size2 + 1.
- Only memcpy from s1 if non-NULL.
- Free old s1 and replace pointer.<br/>Why: Behaves like realloc + append.

### str_append_str
**Correct as-is.**
Just wrapper around str_append_mem with strlen(s2).

> [!IMPORTANT]
> **Add &#34;# ifndef BUFFER_SIZE&#34; and &#34;#endif&#34; between defining BUFFER_SIZE as it will lead to a redefined error when compiling with -D BUFFER_SIZE=xx**

---
## Filter
- Imports required: stdlib.h, unistd.h, string.h, stdio.h
- Input: stdin, Output: Replaces all occurrences of the first argument in the string with asterisks.
- If not defined, define READ_SIZE as 4096 (put at the very top) `#ifndef READ_SIZE -> #define READ_SIZE 4096 -> #endif`
- Not providing only 1 argument or argument is empty will return 1. `argc != 2 || argv[1][0] == '\0'`
- Use read_filter to get stdin data & store in result. `char *result = read_filter(&eof_out);`
- If result is eof, return 0; if result is NULL, return 1. `if (eof_out == EOF) { return 0; } if (!result) { return 1; }`
- Call ft_filter with result & first argument as its arguments. `ft_filter(result, argv[1]);`
- Free result to avoid memory leaks & return 0. `free(result); return 0;`
- static char *read_filter(int *eof_out):
  - Initalizes (char) read buffer with READ_SIZE size, (char *) result as NULL, (size_t) total (read) bytes as 0, (ssize_t) (each read's) bytes.
  - Reads stdin, providing read buffer as buffer & READ_SIZE as size. `bytes = read(STDIN_FILENO, r_buf, READ_SIZE)`
  - Loops the above functionality only if bytes > 0. `while ((...) > 0)`
  - Resize (realloc) the result with the sum of total bytes, bytes and 1, (NUL char) **using a temp to store the return val**. `char *f_buf = realloc(result, total_bytes + (size_t) bytes + 1);`
  - Frees result if the above fails (malloc error) and returns NULL. `if (!f_buf) { return free(result), NULL; }`
  - Set result to the resized result. `result = f_buf;`
  - Append read buffer data to result. `memmove(result + total_bytes, r_buf, (size_t) bytes);`
  - Increment total bytes by bytes. `total_bytes += (size_t) bytes;`
  - Terminate result with NUL char. `result[total_bytes] = '\0';`
  - If bytes < 0, free result & return NULL. (Read error) `if (bytes < 0) { return free(result), NULL; }`
  - If result is NULL, set eof_out flag to EOF & return NULL. `if (!result) { *eof_out = EOF; return NULL; }`
  - Finally, return result.
- static void ft_filter(char *buffer, const char *target):
  - Obtain the string length for both arguments. `size_t t_len = strlen(target); size_t b_len = strlen(buffer);`
  - Use a while loop and an iterator to loop through the buffer. `while (i < b_len)`
  - Use memmem to search for the target string in the buffer starting from i position. `memmem(buffer + i, b_len - i, target, t_len)`
  - If not found, write the remaining buffer data to stdout and return. `write(STDOUT_FILENO, buffer + i, b_len - i);`
  - If found, get the position of the found target string. `size_t hit_pos = (char *) hit - buffer;`
  - Write everything from i position to the match position to stdout. `write(1, buffer + i, hit_pos - i);`
  - Write asterisks equal to the target length to stdout. `for (size_t k = 0; k < t_len; k++) write(STDOUT_FILENO, "*", 1);`
  - Update i to continue searching after the found target string. `i = hit_pos + t_len;`

> [!NOTE]
> - Use pointer arithmetic (+ total_bytes) to append to result when using memmove.
> - Use pointer arithmetic to check for the next occurance in buffer (buffer + i), and reduce the search size by i.
> - Set filter iterator to the sum of match position & target length to setup the next loop.

---
## scanf
- Required imports: stdarg.h, stdio.h, ctype.h
- Reads formatted input from stdin and only required to handle %d, %s, and %c format specifiers.
- Maps the stdin stream to the format string and stores the results in the provided variable arguments (using va_list).
- int ft_scanf(const char *format, ...):
  - Fill in the blanks by initalizing va_list [va_start(ap, format);]
  - Call ft_vfscanf. [ret = ft_vfscanf(stdin, format, ap);]
  - Clean up the va_list. [va_end(ap);]
  - Return the number of successfully assigned input items. [return ret;]
- int ft_vfscanf(FILE *f, const char *format, va_list ap):
  - Use fgetc to check if the stream returns EOF at the start. If so, return EOF.
  - Use ungetc to return the character back to the stream.
  - Loop through the format string until the null terminator [while (*format)].
  - If the current character is a percent sign '%', increment format and call match_conv.
  - If match_conv doesn't return 1 (success), break the loop.
  - If the current character is whitespace, call match_space. Upon failure (EOF), break the loop.
  - If it's a normal character, call match_char. Upon failure (!= 1), break the loop.
  - Increment the format pointer.
  - After the loop, check ferror. If true, return EOF, else return the count of successfully assigned items.
- int match_conv(FILE *f, const char **format, va_list ap):
  - Simple switch statement that matches 'c', 'd', 's' and calls the respective helper functions.
  - Calls match_space for 'd' and 's' to skip leading whitespace.
  - Returns the result of their scan functions or -1 for EOF and unknown cases.
- int scan_char(FILE *f, va_list ap):
  - Use fgetc to get the character and return 0 if it's EOF.
  - Else, store the character into the char pointer provided by va_arg [va_arg(ap, char *)] and return 1.
- int scan_int(FILE *f, va_list ap):
  - Use fgetc and check the sign of the integer ('+' or '-'). If negative, set sign to -1. Override the character variable with the next fgetc.
  - If the character is EOF or not a digit (isdigit), ungetc the character only if the character isn't EOF and return 0. **(Very important to check if EOF is reached as calling isdigit(EOF) is undefined behavior)**
  - Loop while the character is a digit, building the integer value by multiplying the current value by 10 and adding the new digit. (Remember to subtract '0' from the character to get the integer value)
  - Use fgetc to override the character variable for the next iteration.
  - After the loop, if the current character is not EOF, call ungetc on it.
  - Assign the final integer value multipled by the sign to the int pointer provided by va_arg [va_arg(ap, int *)] and return 1.
- int scan_string(FILE *f, va_list ap):
  - Get the char pointer (*p) from va_arg [va_arg(ap, char *)] and duplicate it to a temp variable (*start) for comparison.
  - Use fgetc to get the first character.
  - While the character is not EOF and not whitespace (isspace), store the character inside the given pointer and increment the pointer.
  - Use fgetc to override the character variable for the next iteration.
  - Pad the string with a null terminator after the loop.
  - If the character is not EOF, call ungetc on it.
  - If characters were read (p > start), return 1, else return 0.
- int match_space(FILE *f):
  - Use fgetc to check if current character is EOF. If so, return EOF.
  - While the character is whitespace (isspace), keep calling fgetc.
  - After the loop, if the character is not EOF, call ungetc on it.
  - Return 1 to indicate success.
- int match_char(FILE *f, char c):
  - This function is the fallback in case the character is not '%' or whitespace.
  - Use fgetc to get the character from the stream.
  - If the character is EOF, return EOF.
  - If the character matches the expected character (c), return 1.
  - Else, call ungetc on the character and return 0.

---
## N Queens
- Required imports: stdlib.h, unistd.h
- Write a program to display all solutions for the N-Queens problem for a given N.
- It should format each solution as a list of column positions for each row, separated by spaces, followed by a newline.
- Exits early if no/multiple arguments [argc != 2].
- Use a temp variable to check if the argument is a valid positive integer using pointer arithmetic, exit early if invalid.
- Use atoi to convert the first arg and use malloc to allocate an integer array of size N to store the column positions for each row.
- If malloc fails, exit early.
- Initalize the board array with -1 to indicate no queens are placed.
- Call solve_nqueens with the board, size N, and starting row 0 [solve_n_queens(board, 0, n)].
- Free the board and return 0.
- void solve_n_queens(int *board, int row, int n):
  - If the current row equals N, it means all queens are placed successfully. Use fprintf to write to stdout the solution, then return.
  - If not, loop through each column in the current row.
  - For each column, call is_valid to check if placing a queen at (row, col) is valid.
  - If valid, set board[row] to col (place the queen) and recursively call solve_n_queens for the next row (row + 1).
  - After returning from recursion, reset board[row] to -1 (backtrack).
- int is_valid(int *board, int row, int col):
  - Loop through all previous rows (0 to row) and get the column position.
  - If it equates to that column position, return 0 (invalid).
  - Check if a queen is on both diagonals using ft_abs(prev_col - col) == ft_abs(prev_row - row). If so, return 0 (invalid).
  - If no conflicts found, return 1 (valid).
- int ft_abs(int value):
  - Returns the absolute value of the given integer.
  - If value is negative, return -value, else return value.

---
## Permutations
- Required imports: stdlib.h, unistd.h, stdio.h
- A program that displays all permutations of the given string argument in alphabetical order.
- Exits early if no/empty/multiple arguments.
- Obtains the length of the string, and checks for non-alphabetic characters at the same time. Exits early if found.
- Uses bubble sort to sort the string in alphabetical order.
- Allocates a string (curr) to store the current permutation, and an integer array (used) to track used characters.
- Upon failure, it exits and frees any allocated memory, If successful, it calls backtrack to generate permutations.
- Upon successful backtracking, it frees the allocated memory and returns 0.
- static void bsort(char *s, int len):
  - Just a simple bubble sort implementation. (The usual nested for loops + swapping using tmp variable)
- static void permute(char *s, int len, char *curr, int depth, int *used):
  - If the depth is equal to the length, it means a full valid permutation has been formed and is printed to stdout.
  - Else, loop through each character in the string and if the character is not used, mark it as used and set curr[depth] to that character.
  - Recursively call permute with depth + 1 and after returning, mark the character as unused (backtrack).

---
## Powerset
- Required imports: stdlib.h, stdio.h
- This program takes in an integer followed by a set of distinct integers.
- It is required to display all possible subsets that are able to sum up to the given integer.
- It is also required to follow the input order when displaying the subsets.
- Exits early if there are less than 2 arguments (argc < 3).
- Allocates an integer array to store the set of integers, if malloc fails, exit early.
- Insert the set of integers into the allocated array using atoi.
- The question said they wouldn't test with invalid/duplicate sets, so no need to check for int range/duplicates/non integers/empty strings.
- Create a bitmask variable to represent the subsets that is 2^n where n is the number of integers in the set.
- Loops through the bitmask from 0 to (2^n)-1.
- For each bitmask, it sums the integers that have their corresponding bit set in the bitmask. (2^i, where i is the index of the integer in the set)
- We do this by iterating through the set and checking if (mask & 1ULL << i) is true, if so, add the integer to the sum.
- 1ULL is used instead of 1 to tell the compiler to use an unsigned long long literal instead of an int literal.
- If the sum equals the target integer, we print the subset.
- The subset is printed by iterating through the set again and checking if the bit is set in the mask. (mask & 1ULL << i, same as before)
- We use a first variable so that we can print spaces between the integers, but not before the first integer.
- After printing the subset, we print a newline.
- After iterating through all bitmasks, we free the allocated set array and return 0.

---
## RIP (Balancing Parenthesis)
- Required imports: stdlib.h, stdio.h (Optional: stdbool.h)
- A program that checks if the parenthesis in the given string argument are balanced.
- If it is not balanced, it prints all the possible ways to balance it by replacing the least amount of parenthesis with spaces.
- Exits early if no/empty/multiple arguments.
- Obtains the minimum replacements needed to balance the parenthesis using compute_rem.
- If it is already balanced (st.rem == 0 && is_balanced), it prints the original string and exits.
- It then calls backtrack to find all possible balanced strings.
- void compute_rem(const char *s, int *rem):
  - Computes the minimum number of replacements needed to balance the parenthesis.
  - A positive number indicates excess opening parenthesis, while a negative number indicates excess closing parenthesis.
  - While checking, if a non-parenthesis character is found, it exits early.
- bool is_balanced(char *s):
  - Loops through the string and uses a counter to track the balance of parenthesis.
  - Increments the counter for '(' and decrements for ')'.
  - If the counter goes negative at any point, it returns false.
  - At the end, if the counter is zero, it returns true, else false.
- void backtrack(char *s, int index, int rem, int *found):
  - If the index (i) is equal to the string length, it checks for any remaining balance (st.bal), rem (st.rem) and if the string is balanced.
  - If these conditions are met, it prints the string.
  - If the index is less than the string length, it checks if there is any remainder (st.rem > 0).
  - If so, it replaces the current character with a space and recursively calls backtrack. [backtrack(s, len, i + 1, (t_state){st.rem - 1, st.bal})]
  - After returning, it restores the original character.
  - Then it stores the value of the parenthesis (delta). (1 for '(', -1 for ')').
  - With this value, it moves the index forward and updates the balance according to the value calculated above. [backtrack(s, len, i + 1, (t_state){st.rem, st.bal + delta})]

---
## TSP (Traveling Salesman Problem)
- Required imports: stdio.h, math.h (Optional: stdbool.h)
- Remember to compile with -lm **AFTER THE SOURCES** to link the math library.
- Parse the stdin input to obtain the number of cities and their coordinates using fscanf.
- Since it is explicitly stated that the number of cities will not be tested with more than 11 cities, a fixed size 11 array can be used to store the coordinates.
- Prints 0.00 and exits early if given less than 2 cities since no need to travel anywhere.
- Initializes n, x and y with the given inputs and best_len with FLT_MAX or 3.4e38f as an alternative.
- Also initializes the path to 0 and used to true for the first city.
- It calls backtrack with the level being 1 (since the first city is fixed) and curr_len being 0.0f (as initialized).
- Once done, it prints the best length found with 2 decimal places as required since the form expected is "%.2f".
- static void backtrack(TSPState *s, int level, float curr_len):
  - If the level/depth equals the number of cities, it means a full path has been formed.
  - It then adds the distance from the last city back to the first city to compute the total length using the dist function.
  - If total length is less than the best length found so far, it updates the best length.
  - If level is less than the number of cities, it loops through each city.
  - If city is not used, it calculates the new length by adding the distance from the last city using the dist function.
  - If new length exceeds the best length, it skips further exploration (pruning).
  - If not, it marks the city as used, sets path[level] to the city index and sets used[city] to true.
  - It then recursively calls backtrack with level + 1 and new_len. [backtrack(s, level + 1, new_len)]
  - After returning, it sets the city as unused (backtrack).
- static inline float dist(float *x, float *y, int a, int b):
  - Calculates the Euclidean distance between two cities using their coordinates. (Pythagorean theorem: sqrt(x^2 + y^2))
