#!/bin/bash
# Tests for RPN: tests/tests.sh (builds the program, then checks every case below).
#
# A valid expression prints its result on stdout, nothing on stderr, and exits with 0.
# An invalid one prints "Error" on stderr, nothing on stdout, and exits with 1.
# Results are computed in a 64-bit long: the limit tests are skipped where long is smaller.

cd "$(dirname "$0")/.." || exit 1
make -s || exit 1

TMP=$(mktemp -d) || exit 1
trap 'rm -rf "${TMP:?}"' EXIT

PASSED=0
FAILED=0

# run ARGUMENTS...: runs RPN and saves its exit status, stdout and stderr
run() {
	: > "$TMP/stderr"
	STDOUT=$(./RPN "$@" 2> "$TMP/stderr")
	STATUS=$?
	STDERR=$(cat "$TMP/stderr")
}

# check DESCRIPTION EXPECTED_STATUS EXPECTED_STDOUT EXPECTED_STDERR: compares with the last run
check() {
	local details=""
	if [ "$STATUS" != "$2" ]; then
		details="${details}      exit status: expected $2, got $STATUS"$'\n'
	fi
	if [ "$STDOUT" != "$3" ]; then
		details="${details}      stdout expected: [$3]"$'\n'"      stdout got:      [$STDOUT]"$'\n'
	fi
	if [ "$STDERR" != "$4" ]; then
		details="${details}      stderr expected: [$4]"$'\n'"      stderr got:      [$STDERR]"$'\n'
	fi
	if [ -z "$details" ]; then
		PASSED=$((PASSED + 1))
		printf 'OK  %s\n' "$1"
	else
		FAILED=$((FAILED + 1))
		printf 'KO  %s\n%s' "$1" "$details" | cut -c 1-300
	fi
}

# shown EXPRESSION: the expression itself when short, its length otherwise
shown() {
	if [ "${#1}" -le 60 ]; then
		printf '"%s"' "$1"
	else
		printf '(%d characters)' "${#1}"
	fi
}

# expect_result DESCRIPTION EXPRESSION RESULT
expect_result() {
	run "$2"
	check "$1: $(shown "$2") = $3" 0 "$3" ""
}

# expect_error DESCRIPTION ARGUMENTS...
expect_error() {
	local description=$1
	shift
	run "$@"
	check "$description${1+: $(shown "$1")}" 1 "" "Error"
}

# power BASE EXPONENT: an expression computing BASE^EXPONENT, as "BASE BASE * BASE * ..."
power() {
	local expression=$1 i
	for ((i = 1; i < $2; i++)); do
		expression="$expression $1 *"
	done
	echo "$expression"
}

echo "== Subject"
expect_result "subject" "8 9 * 9 - 9 - 9 - 4 - 1 +" 42
expect_result "subject" "7 7 * 7 -" 42
expect_result "subject" "1 2 * 2 / 2 * 2 4 - +" 0
expect_error "subject: brackets" "(1 + 1)"

echo "== Evaluation sheet"
expect_result "evaluation" "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -" 42
expect_result "evaluation, trailing space" "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 / " 15

echo "== Each operator"
expect_result "addition" "1 1 +" 2
expect_result "addition" "9 9 +" 18
expect_result "subtraction, left minus right" "5 3 -" 2
expect_result "subtraction, negative result" "3 5 -" -2
expect_result "multiplication" "4 3 *" 12
expect_result "multiplication" "9 9 *" 81
expect_result "division, left divided by right" "8 2 /" 4
expect_result "division, left divided by right" "8 4 /" 2
expect_result "division, rounded towards zero" "4 8 /" 0
expect_result "division, rounded towards zero" "7 2 /" 3
expect_result "division, rounded towards zero, not down" "0 7 - 2 /" -3
expect_result "division of two negative numbers" "0 7 - 0 2 - /" 3
expect_result "division by a negative number" "9 0 9 - /" -1

echo "== Single numbers"
for digit in 0 1 2 3 4 5 6 7 8 9; do
	expect_result "a digit alone" "$digit" "$digit"
done
expect_result "every digit, all on the stack before the operators" "0 1 2 3 4 5 6 7 8 9 + + + + + + + + +" 45

echo "== Zero"
expect_result "0 + 0" "0 0 +" 0
expect_result "0 - 5" "0 5 -" -5
expect_result "5 * 0" "5 0 *" 0
expect_result "0 / 5" "0 5 /" 0
expect_result "0 * 0" "0 0 *" 0

echo "== Negative numbers"
expect_result "negative times positive" "0 9 - 9 *" -81
expect_result "negative times negative" "0 9 - 0 9 - *" 81
expect_result "negative plus positive" "0 9 - 9 +" 0
expect_result "negative minus positive" "0 9 - 9 -" -18
expect_result "negative minus negative" "0 9 - 0 9 - -" 0
expect_result "negative divided by positive" "0 9 - 2 /" -4

echo "== Whitespace"
expect_result "leading and trailing spaces" "   1 2 +   " 3
expect_result "several spaces" "1     2     +" 3
expect_result "tabs" $'1\t2\t+' 3
expect_result "newlines" $'1\n2\n+' 3
expect_result "mixed" $'\t 3 \n 4 \t * \n' 12

echo "== Long expressions"
LONG_SUM="1"
DEEP_STACK="9"
OPERATORS=""
for ((i = 1; i < 1000; i++)); do
	LONG_SUM="$LONG_SUM 1 +"
	DEEP_STACK="$DEEP_STACK 9"
	OPERATORS="$OPERATORS +"
done
expect_result "1000 numbers, added one at a time" "$LONG_SUM" 1000
expect_result "1000 numbers on the stack, then 999 operators" "$DEEP_STACK$OPERATORS" 9000

if [ "$(getconf LONG_BIT)" = 64 ]; then
	echo "== Big numbers (64-bit long)"
	LONG_MAX="$(power 4 31) 1 - $(power 4 31) +"
	LONG_MIN="0 $(power 4 31) - $(power 4 31) -"
	expect_result "9^19" "$(power 9 19)" 1350851717672992089
	expect_result "-(9^19)" "0 $(power 9 19) -" -1350851717672992089
	expect_result "LONG_MAX = 2 * 4^31 - 1" "$LONG_MAX" 9223372036854775807
	expect_result "LONG_MIN = -2 * 4^31" "$LONG_MIN" -9223372036854775808
	expect_result "LONG_MAX * -1" "$LONG_MAX 0 1 - *" -9223372036854775807
	expect_result "LONG_MIN / 1" "$LONG_MIN 1 /" -9223372036854775808
	expect_result "LONG_MIN + LONG_MAX" "$LONG_MIN $LONG_MAX +" -1
	expect_result "LONG_MAX / LONG_MAX" "$LONG_MAX $LONG_MAX /" 1
	expect_result "LONG_MIN / LONG_MIN" "$LONG_MIN $LONG_MIN /" 1
	expect_result "LONG_MAX - LONG_MAX" "$LONG_MAX $LONG_MAX -" 0

	echo "== Overflow: Error instead of a wrong result"
	expect_error "9^20" "$(power 9 20)"
	expect_error "negative times positive: -9 * 9^19" "0 9 - $(power 9 19) *"
	expect_error "negative times negative: -9 * -(9^19)" "0 9 - 0 $(power 9 19) - *"
	expect_error "LONG_MAX + 1" "$LONG_MAX 1 +"
	expect_error "LONG_MAX - -1" "$LONG_MAX 0 1 - -"
	expect_error "LONG_MIN - 1" "$LONG_MIN 1 -"
	expect_error "LONG_MIN + -1" "$LONG_MIN 0 1 - +"
	expect_error "0 - LONG_MIN" "0 $LONG_MIN -"
	expect_error "LONG_MAX * 2" "$LONG_MAX 2 *"
	expect_error "LONG_MIN * 2" "$LONG_MIN 2 *"
	expect_error "LONG_MIN * -1" "$LONG_MIN 0 1 - *"
	expect_error "LONG_MIN / -1" "$LONG_MIN 0 1 - /"
else
	echo "--  big number and overflow tests skipped: long is not 64-bit here"
fi

echo "== Division by zero"
expect_error "division by zero" "1 0 /"
expect_error "zero divided by zero" "0 0 /"
expect_error "divisor computed to zero" "5 3 3 - /"

echo "== Invalid tokens"
expect_error "closing bracket" "1 2 + )"
expect_error "number with 2 digits" "10 2 +"
expect_error "number with 2 digits" "1 22 +"
expect_error "negative number written directly" "-1 2 +"
expect_error "number with a plus sign" "+1 2 +"
expect_error "decimal number" "1.5 2 +"
expect_error "decimal comma" "1,5 2 +"
expect_error "letter" "a"
expect_error "letter among numbers" "1 a +"
expect_error "modulo" "1 2 %"
expect_error "power" "1 2 ^"
expect_error "x as multiplication" "1 2 x"
expect_error "operator written twice" "1 2 ++"
expect_error "no spaces" "12+"
expect_error "operator stuck to a number" "1 2+"
expect_error "number stuck to an operator" "1 2 + 3+"
expect_error "Unicode minus sign" "1 2 −"
expect_error "full-width digits" "１ ２ +"

echo "== Wrong number of operands"
expect_error "empty expression" ""
expect_error "spaces only" "   "
expect_error "whitespace only" $'\t\n'
expect_error "operator alone" "+"
expect_error "one operand" "1 +"
expect_error "no operator" "1 2"
expect_error "operand left over" "1 2 3 +"
expect_error "operand left over at the end" "1 2 + 3"
expect_error "second operator without operand" "1 2 + +"
expect_error "prefix notation" "+ 1 2"
expect_error "infix notation" "1 + 2"

echo "== Arguments"
expect_error "no argument"
expect_error "two arguments" "1 2 +" "3"
expect_error "one token per argument" "1" "2" "+"

echo "== Memory (valgrind)"
if command -v valgrind > /dev/null 2>&1; then
	for expression in "8 9 * 9 - 9 - 9 - 4 - 1 +" "1 0 /" "1 2" "(1 + 1)" "$DEEP_STACK$OPERATORS"; do
		valgrind -q --leak-check=full --error-exitcode=42 ./RPN "$expression" > /dev/null 2> "$TMP/valgrind"
		STATUS=$?
		STDOUT=""
		STDERR=$(grep '^==[0-9]*==' "$TMP/valgrind")
		[ "$STATUS" -ne 42 ] && STATUS=0
		check "no leak or memory error: ./RPN $(shown "$expression")" 0 "" ""
	done
else
	echo "--  skipped: valgrind is not installed"
fi

echo "== $PASSED passed, $FAILED failed"
[ "$FAILED" -eq 0 ]
