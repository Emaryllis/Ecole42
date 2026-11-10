#!/bin/bash
# Tests for PmergeMe: tests/tests.sh (builds the program, then checks every case below).
#
# Each sorting test checks that the program exits with 0 and prints exactly 4 lines:
#   Before: the numbers in their original order
#   After:  the same numbers sorted (compared with sort -n)
#   "Time to process a range of N elements with std::vector : T us", then the same line for std::deque
# Only the std::vector result is printed: the program itself checks that std::deque holds the same sorted
# sequence, and prints Error if it does not.
# Each error test checks that the program exits with 1, prints "Error" on stderr and nothing on stdout.

cd "$(dirname "$0")/.." || exit 1
make -s || exit 1

TMP=$(mktemp -d) || exit 1
trap 'rm -rf "${TMP:?}"' EXIT

PASSED=0
FAILED=0
OUTPUT=""

report() {
	if [ "$1" -eq 0 ]; then
		PASSED=$((PASSED + 1))
		printf 'OK  %s\n' "$2"
	else
		FAILED=$((FAILED + 1))
		printf 'KO  %s\n' "$2"
		printf '%s\n' "$OUTPUT" | cut -c 1-200 | sed 's/^/      /'
	fi
}

# random_numbers COUNT MAX: COUNT numbers from 1 to MAX, repeats allowed (the evaluation sheet's commands)
random_numbers() {
	if command -v shuf > /dev/null 2>&1; then
		shuf -r -i 1-"$2" -n "$1" | tr '\n' ' '
	else
		jot -r "$1" 1 "$2" | tr '\n' ' '
	fi
}

# pattern NAME COUNT: COUNT numbers following the pattern NAME
PATTERNS="random sorted reversed all_equal three_values zigzag up_then_down near_INT_MAX"
pattern() {
	awk -v name="$1" -v n="$2" -v seed="$RANDOM" 'BEGIN {
		srand(seed)
		for (i = 1; i <= n; i++) {
			if (name == "sorted") v = i
			else if (name == "reversed") v = n - i + 1
			else if (name == "all_equal") v = 7
			else if (name == "three_values") v = 1 + int(rand() * 3)
			else if (name == "zigzag") v = (i % 2) ? i : 2 * n - i
			else if (name == "up_then_down") v = (i <= n / 2) ? i : n - i + 1
			else if (name == "near_INT_MAX") v = 2147483647 - int(rand() * 1000)
			else v = 1 + int(rand() * 1000000)
			printf "%d ", v
		}
	}'
}

# permutations PREFIX ITEMS...: every order of ITEMS, one per line, each after PREFIX
permutations() {
	local prefix=$1 item other rest
	shift
	if [ $# -eq 0 ]; then
		echo "$prefix"
		return
	fi
	for item in "$@"; do
		rest=""
		for other in "$@"; do
			[ "$other" != "$item" ] && rest="$rest $other"
		done
		permutations "$prefix $item" $rest
	done
}

# is_sorted_correctly NUMBERS...: runs the program and checks its output, without printing anything
is_sorted_correctly() {
	local status input expected count
	OUTPUT=$(./PmergeMe "$@" 2>&1)
	status=$?
	input=$(echo $*)
	count=$(printf '%s\n' $input | wc -l | tr -d ' ')
	expected=$(printf '%s\n' $input | sort -n | tr '\n' ' ' | sed 's/ $//')
	[ "$status" -eq 0 ] &&
		[ "$(printf '%s\n' "$OUTPUT" | wc -l | tr -d ' ')" -eq 4 ] &&
		[ "$(printf '%s\n' "$OUTPUT" | sed -n 1p)" = "Before: $input" ] &&
		[ "$(printf '%s\n' "$OUTPUT" | sed -n 2p)" = "After: $expected" ] &&
		printf '%s\n' "$OUTPUT" | sed -n 3p |
		grep -Eq "^Time to process a range of $count elements with std::vector : [0-9]+\.[0-9]+ us$" &&
		printf '%s\n' "$OUTPUT" | sed -n 4p |
		grep -Eq "^Time to process a range of $count elements with std::deque +: [0-9]+\.[0-9]+ us$"
}

expect_sorted() {
	local description=$1
	shift
	is_sorted_correctly "$@"
	report $? "$description"
}

# expect_output DESCRIPTION BEFORE AFTER ARGUMENTS...: exact "Before:" and "After:" lines
expect_output() {
	local description=$1 before=$2 after=$3 status
	shift 3
	OUTPUT=$(./PmergeMe "$@" 2>&1)
	status=$?
	[ "$status" -eq 0 ] &&
		[ "$(printf '%s\n' "$OUTPUT" | wc -l | tr -d ' ')" -eq 4 ] &&
		[ "$(printf '%s\n' "$OUTPUT" | sed -n 1p)" = "Before: $before" ] &&
		[ "$(printf '%s\n' "$OUTPUT" | sed -n 2p)" = "After: $after" ]
	report $? "$description"
}

expect_error() {
	local description=$1 stdout stderr status
	shift
	stdout=$(./PmergeMe "$@" 2> "$TMP/stderr")
	status=$?
	stderr=$(cat "$TMP/stderr")
	OUTPUT="exit $status, stdout: [$stdout], stderr: [$stderr]"
	[ "$status" -eq 1 ] && [ -z "$stdout" ] && [ "$stderr" = "Error" ]
	report $? "$description"
}

# expect_permutations DESCRIPTION VALUES...: every order of the values, given by position so repeats work
expect_permutations() {
	local description=$1 order position numbers failures="" count=0
	shift
	local values=("$@")
	while read -r order; do
		numbers=""
		for position in $order; do
			numbers="$numbers ${values[$position]}"
		done
		count=$((count + 1))
		is_sorted_correctly $numbers || failures="$failures [$numbers]"
	done < <(permutations "" $(seq 0 $(($# - 1))))
	OUTPUT="failed orders:$failures"
	[ -z "$failures" ]
	report $? "$description ($count orders)"
}

# expect_patterns DESCRIPTION SIZES...: every pattern at every size, one result line per pattern
expect_patterns() {
	local description=$1 name size failures
	shift
	for name in $PATTERNS; do
		failures=""
		for size in "$@"; do
			is_sorted_correctly $(pattern "$name" "$size") || failures="$failures $size"
		done
		OUTPUT="failed sizes:$failures"
		[ -z "$failures" ]
		report $? "$name, $description"
	done
}

echo "== Subject and evaluation sheet"
expect_sorted "subject example: 3 5 9 7 4" 3 5 9 7 4
expect_sorted "evaluation: 5 to 10 different positive integers" 42 7 19 3 88 1 56 23
expect_sorted "evaluation: 3000 numbers from 1 to 1000, with repeats" $(random_numbers 3000 1000)
expect_sorted "subject: 3000 numbers from 1 to 100000" $(random_numbers 3000 100000)

echo "== Small inputs"
expect_sorted "one number" 42
expect_sorted "INT_MAX alone" 2147483647
expect_sorted "two numbers in order" 1 2
expect_sorted "two numbers out of order" 2 1
expect_sorted "two equal numbers" 5 5
expect_permutations "every order of 3 numbers" 1 2 3
expect_permutations "every order of 4 numbers" 1 2 3 4
expect_permutations "every order of 5 numbers" 1 2 3 4 5
expect_permutations "every order of 6 numbers" 1 2 3 4 5 6
expect_permutations "every order of 5 numbers with repeats" 1 1 2 2 3

echo "== Accepted number formats"
expect_output "plus sign and leading zeros" "5 7 1 10" "1 5 7 10" +5 007 00000000000000000000001 +010
expect_output "several numbers in one argument" "3 5 9 7 4 1" "1 3 4 5 7 9" "3 5 9" 7 "4 1"
expect_output "tabs, newlines and extra spaces in arguments" "3 5 9 1" "1 3 5 9" $' 3\t5\n9 ' "  1  "
expect_output "1 and INT_MAX" "2147483647 1 2147483647 1" "1 1 2147483647 2147483647" 2147483647 1 2147483647 1

echo "== Repeated numbers"
expect_sorted "repeats" 5 3 5 3 1 1 5
expect_sorted "all equal" 7 7 7 7 7 7 7
expect_sorted "1 and INT_MAX repeated" 2147483647 1 2 2147483646 1 2147483647

echo "== Patterns: $PATTERNS"
expect_patterns "every size from 1 to 64" $(seq 1 64)
expect_patterns "sizes around Jacobsthal numbers 21 to 2731" 21 22 23 42 43 44 85 86 87 170 171 172 341 342 343 \
	682 683 684 1365 1366 1367 2730 2731 2732
expect_patterns "sizes around powers of 2 from 128 to 4096" 127 128 129 255 256 257 511 512 513 1023 1024 1025 \
	2047 2048 2049 4095 4096 4097

echo "== Large inputs"
expect_sorted "10000 numbers from 1 to 1000000" $(random_numbers 10000 1000000)
expect_sorted "10000 numbers from 1 to 10" $(random_numbers 10000 10)

echo "== Errors"
expect_error "no argument"
expect_error "subject: -1 2" "-1" "2"
expect_error "0" 0
expect_error "0 with a plus sign" +0
expect_error "0 with leading zeros" 000
expect_error "0 among valid numbers" 3 5 0 9
expect_error "0 inside an argument" "3 0 9"
expect_error "negative zero" -0
expect_error "INT_MIN" -2147483648
expect_error "negative number inside an argument" "1 -2 3"
expect_error "minus sign alone" -
expect_error "plus sign alone" +
expect_error "two plus signs" ++1
expect_error "plus then minus" +-1
expect_error "two minus signs" --1
expect_error "plus sign after the digits" 1+
expect_error "minus sign after the digits" 1-
expect_error "letters" abc
expect_error "number followed by letters" 12a
expect_error "letters followed by a number" a12
expect_error "word among numbers" 1 2 three
expect_error "decimal number" 1.5
expect_error "decimal comma" 1,5
expect_error "exponent" 1e3
expect_error "hexadecimal" 0x10
expect_error "INT_MAX + 1" 2147483648
expect_error "2^32" 4294967296
expect_error "far above INT_MAX" 99999999999999999999
expect_error "valid number, then one too large" 2147483647 2147483648
expect_error "empty argument between numbers" 1 "" 2
expect_error "empty argument alone" ""
expect_error "argument with only spaces" "   "
expect_error "argument with only a tab" $'\t'
expect_error "Arabic-Indic digit" "٣"
expect_error "full-width digit" "３"
expect_error "error after 3000 valid numbers: nothing printed on stdout" $(seq 1 3000) x

echo "== Ford-Johnson comparison count (separate build, the sources are not changed)"
# A copy of PmergeMe.cpp counts every comparison between two numbers. Merge-insertion never needs more than
# F(n) = sum of ceil(log2(3k / 4)) for k from 1 to n comparisons (Knuth, TAOCP Vol. 3, 5.3.1).
mkdir "$TMP/counted"
{
	echo 'extern unsigned long g_vectorComparisons;'
	echo 'extern unsigned long g_dequeComparisons;'
	sed -e '/^void PmergeMe::sortVector/,/^}/ s/if (\*(b + unitSize - 1) > \*(a + unitSize - 1))/if (++g_vectorComparisons, *(b + unitSize - 1) > *(a + unitSize - 1))/' \
		-e '/^void PmergeMe::sortDeque/,/^}/ s/if (\*(b + unitSize - 1) > \*(a + unitSize - 1))/if (++g_dequeComparisons, *(b + unitSize - 1) > *(a + unitSize - 1))/' \
		-e 's/if (key < _vector\[/if (++g_vectorComparisons, key < _vector[/' \
		-e 's/if (key < _deque\[/if (++g_dequeComparisons, key < _deque[/' PmergeMe.cpp
} > "$TMP/counted/PmergeMe.cpp"
cat > "$TMP/counted/main.cpp" << 'EOF'
#include <iostream>
#include "PmergeMe.hpp"

unsigned long g_vectorComparisons = 0;
unsigned long g_dequeComparisons = 0;

int main(int argc, char **argv) {
	PmergeMe sorter;
	sorter.run(argc, argv);
	std::cerr << g_vectorComparisons << ' ' << g_dequeComparisons << std::endl;
	return 0;
}
EOF
INSTRUMENTED=$(grep -c '++g_' "$TMP/counted/PmergeMe.cpp")
OUTPUT="expected 4 counted comparisons in the copy, found $INSTRUMENTED: the comparison lines in PmergeMe.cpp changed"
[ "$INSTRUMENTED" -eq 4 ] && c++ -std=c++98 -O2 -I. "$TMP/counted/PmergeMe.cpp" "$TMP/counted/main.cpp" \
	-o "$TMP/counted/PmergeMe" 2> "$TMP/counted/build.log"
report $? "counting copy built"

# max_comparisons N: F(N), with integers only: ceil(log2(3k / 4)) is the smallest j with 2^(j + 2) >= 3k
max_comparisons() {
	awk -v n="$1" 'BEGIN { for (k = 1; k <= n; k++) { j = 0; while (2 ^ (j + 2) < 3 * k) j++; total += j } print total + 0 }'
}

OUTPUT="F(5) = $(max_comparisons 5), F(21) = $(max_comparisons 21), F(100) = $(max_comparisons 100)"
[ "$(max_comparisons 5)" -eq 7 ] && [ "$(max_comparisons 21)" -eq 66 ] && [ "$(max_comparisons 100)" -eq 534 ]
report $? "F(n) formula gives the known values F(5) = 7, F(21) = 66, F(100) = 534"

# expect_comparisons DESCRIPTION SIZES...: random inputs and inputs with repeats, at most F(n) comparisons
expect_comparisons() {
	local description=$1 size name bound counts vector deque failures=""
	shift
	for size in "$@"; do
		bound=$(max_comparisons "$size")
		for name in random three_values reversed; do
			counts=$("$TMP/counted/PmergeMe" $(pattern "$name" "$size") 2>&1 > /dev/null)
			vector=${counts% *}
			deque=${counts#* }
			if [ "$vector" -gt "$bound" ] || [ "$deque" -ne "$vector" ]; then
				failures="$failures n=$size:$name:vector=$vector,deque=$deque,F=$bound"
			fi
		done
	done
	OUTPUT="above F(n) or different between containers:$failures"
	[ -z "$failures" ]
	report $? "$description"
}

if [ -x "$TMP/counted/PmergeMe" ]; then
	expect_comparisons "at most F(n) comparisons, same count for both containers, sizes 1 to 100" $(seq 1 100)
	expect_comparisons "at most F(n) comparisons, same count for both containers, sizes 1000 and 3000" 1000 3000
fi

echo "== Memory (valgrind)"
if command -v valgrind > /dev/null 2>&1; then
	for case in "3 5 9 7 4" "$(random_numbers 3000 1000)" "1 -2" "42" ""; do
		valgrind -q --leak-check=full --error-exitcode=42 ./PmergeMe $case > /dev/null 2> "$TMP/valgrind"
		[ $? -ne 42 ] && ! grep -q '^==[0-9]*==' "$TMP/valgrind"
		STATUS=$?
		OUTPUT=$(cat "$TMP/valgrind")
		report $STATUS "no leak or memory error: ./PmergeMe $(echo $case | cut -c 1-30)"
	done
else
	echo "--  skipped: valgrind is not installed"
fi

echo "== $PASSED passed, $FAILED failed"
[ "$FAILED" -eq 0 ]
