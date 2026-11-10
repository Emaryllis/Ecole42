#!/bin/bash
# Tests for btc: tests/tests.sh (builds the program, then checks every case below).
#
# Each test checks the exit status, stdout and stderr separately:
#   - every line of the input file gets one line on stdout, errors included, and the whole file is processed
#   - errors that stop the program (arguments, input file, database) go to stderr, with exit status 1
# Expected results come from data.csv: the rate of the input date, or of the closest earlier date.

cd "$(dirname "$0")/.." || exit 1
make -s || exit 1

BTC="$PWD/btc"
# data.csv and input.txt are downloaded with the subject, so they are kept here, next to the tests.
# btc reads data.csv from the directory it is run from: run it from tests/.
cd tests || exit 1
TMP=$(mktemp -d) || exit 1
trap 'chmod -R u+rwx "${TMP:?}" 2> /dev/null; rm -rf "${TMP:?}"' EXIT

PASSED=0
FAILED=0

# run DIRECTORY ARGUMENTS...: runs btc from DIRECTORY and saves its exit status, stdout and stderr
run() {
	local directory=$1
	shift
	: > "$TMP/stderr"
	STDOUT=$(cd "$directory" && "$BTC" "$@" 2> "$TMP/stderr")
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

# expect_line DESCRIPTION LINE EXPECTED_STDOUT: LINE is written after the header of a new input file
expect_line() {
	printf 'date | value\n%s\n' "$2" > "$TMP/input.txt"
	run . "$TMP/input.txt"
	check "$1: [$2]" 0 "$3" ""
}

# expect_file DESCRIPTION CONTENT STATUS STDOUT STDERR: CONTENT is the whole input file, written as is
expect_file() {
	printf '%s' "$2" > "$TMP/input.txt"
	run . "$TMP/input.txt"
	check "$1" "$3" "$4" "$5"
}

# expect_database DESCRIPTION DATABASE INPUT STATUS STDOUT STDERR: runs btc next to DATABASE as data.csv
expect_database() {
	rm -rf "${TMP:?}/database"
	mkdir "$TMP/database"
	printf '%s' "$2" > "$TMP/database/data.csv"
	printf '%s' "$3" > "$TMP/input.txt"
	run "$TMP/database" "$TMP/input.txt"
	check "$1" "$4" "$5" "$6"
}

# database_error DESCRIPTION LINE REASON: LINE is the 3rd line of data.csv, after the header and a valid rate
database_error() {
	expect_database "$1" $'date,exchange_rate\n2011-01-01,2\n'"$2"$'\n' $'date | value\n2011-01-05 | 1\n' \
		1 "" "Error: data.csv line 3: $3 => $2"
}

# macOS's C++ library reads a directory like an empty file instead of failing: accept its message there too
accept_directory_as_empty_on_macos() {
	if [ "$(uname)" = Darwin ] && [ "$STDERR" = "$1" ]; then
		STDERR=$2
	fi
}

echo "== Subject example"
run . input.txt
check "./btc input.txt gives the subject's output" 0 "2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number." ""
run . edge_cases.txt
STDOUT=$(printf '%s\n' "$STDOUT" | wc -l | tr -d ' ')
check "./btc edge_cases.txt: one output line for each of its 68 lines after the header" 0 "68" ""

echo "== Arguments"
run .
check "no argument" 1 "" "Error: could not open file."
run . input.txt input.txt
check "two arguments" 1 "" "Error: too many arguments."
run . does_not_exist.txt
check "file that does not exist" 1 "" "Error: could not open file."
run . ""
check "empty file name" 1 "" "Error: could not open file."
run . "$TMP"
accept_directory_as_empty_on_macos "Error: file is empty." "Error: could not read file."
check "directory instead of a file" 1 "" "Error: could not read file."
printf 'date | value\n2011-01-03 | 3\n' > "$TMP/unreadable.txt"
chmod 000 "$TMP/unreadable.txt"
if [ -r "$TMP/unreadable.txt" ]; then
	echo "--  file without read permission: skipped, root can read it anyway"
else
	run . "$TMP/unreadable.txt"
	check "file without read permission" 1 "" "Error: could not open file."
fi

echo "== Input file"
expect_file "empty file" "" 1 "" "Error: file is empty."
expect_file "header only" $'date | value\n' 0 "" ""
expect_file "header only, without newline" "date | value" 0 "" ""
expect_file "a single empty line" $'\n' 0 "Error: bad input => " ""
expect_file "no header: the first line is data" $'2011-01-03 | 3\n' 0 "2011-01-03 => 3 = 0.9" ""
expect_file "header written differently is bad input" $'Date | Value\n2011-01-03 | 3\n' 0 \
	$'Error: bad input => Date | Value\n2011-01-03 => 3 = 0.9' ""
expect_file "header again in the middle is bad input" $'date | value\n2011-01-03 | 3\ndate | value\n2011-01-03 | 1\n' 0 \
	$'2011-01-03 => 3 = 0.9\nError: bad input => date | value\n2011-01-03 => 1 = 0.3' ""
expect_file "last line without newline" $'date | value\n2011-01-03 | 3\n2011-01-03 | 2' 0 \
	$'2011-01-03 => 3 = 0.9\n2011-01-03 => 2 = 0.6' ""
expect_file "Windows line endings (CRLF)" $'date | value\r\n2011-01-03 | 3\r\n2011-01-03 | -1\r\n' 0 \
	$'2011-01-03 => 3 = 0.9\nError: not a positive number.' ""
expect_file "UTF-8 byte order mark before the header" $'\xEF\xBB\xBFdate | value\n2011-01-03 | 3\n' 0 \
	"2011-01-03 => 3 = 0.9" ""
expect_file "byte order mark and CRLF together" $'\xEF\xBB\xBFdate | value\r\n2011-01-03 | 3\r\n' 0 \
	"2011-01-03 => 3 = 0.9" ""
expect_file "byte order mark on another line is bad input" $'date | value\n\xEF\xBB\xBF2011-01-03 | 3\n' 0 \
	$'Error: bad input => \xEF\xBB\xBF2011-01-03 | 3' ""
expect_file "empty line between two valid lines" $'date | value\n2011-01-03 | 3\n\n2011-01-03 | 2\n' 0 \
	$'2011-01-03 => 3 = 0.9\nError: bad input => \n2011-01-03 => 2 = 0.6' ""
expect_file "every kind of error, then a valid line: nothing stops the program" \
	$'date | value\n2001-42-42\n2013-02-29 | 1\n2011-01-03 | -1\n2011-01-03 | 1001\n2009-01-01 | 1\n2011-01-03 | 3\n' 0 \
	$'Error: bad input => 2001-42-42\nError: invalid date => 2013-02-29\nError: not a positive number.\nError: too large a number.\nError: no exchange rate available before 2009-01-02 => 2009-01-01\n2011-01-03 => 3 = 0.9' ""
expect_file "binary garbage" $'date | value\n\x01\x02\x7f | \x03\n' 0 $'Error: bad input => \x01\x02\x7f | \x03' ""
LONG_LINE=$(printf '%100000s' "" | tr ' ' 'a')
expect_file "100000 character line" $'date | value\n'"$LONG_LINE"$'\n' 0 "Error: bad input => $LONG_LINE" ""
awk 'BEGIN { print "date | value"; for (i = 0; i < 10000; i++) print "2011-01-03 | 3" }' > "$TMP/big.txt"
run . "$TMP/big.txt"
STDOUT=$(printf '%s\n' "$STDOUT" | grep -c '^2011-01-03 => 3 = 0.9$')
check "10000 lines: all of them processed" 0 "10000" ""

echo "== Leap years"
expect_line "divisible by 4" "2012-02-29 | 1" "2012-02-29 => 1 = 4.98"
expect_line "divisible by 4" "2016-02-29 | 1" "2016-02-29 => 1 = 431.89"
expect_line "divisible by 4" "2020-02-29 | 1" "2020-02-29 => 1 = 8712.35"
expect_line "not divisible by 4" "2013-02-29 | 1" "Error: invalid date => 2013-02-29"
expect_line "not divisible by 4" "2014-02-29 | 1" "Error: invalid date => 2014-02-29"
expect_line "not divisible by 4" "2015-02-29 | 1" "Error: invalid date => 2015-02-29"
expect_line "not divisible by 4" "2021-02-29 | 1" "Error: invalid date => 2021-02-29"
expect_line "century not divisible by 400" "1900-02-29 | 1" "Error: invalid date => 1900-02-29"
expect_line "century not divisible by 400" "2100-02-29 | 1" "Error: invalid date => 2100-02-29"
expect_line "century not divisible by 400" "2200-02-29 | 1" "Error: invalid date => 2200-02-29"
expect_line "century not divisible by 400" "2300-02-29 | 1" "Error: invalid date => 2300-02-29"
expect_line "divisible by 400, before the database" "2000-02-29 | 1" \
	"Error: no exchange rate available before 2009-01-02 => 2000-02-29"
expect_line "divisible by 400, after the database" "2400-02-29 | 1" "2400-02-29 => 1 = 47115.93"
expect_line "year 0000 is divisible by 400" "0000-02-29 | 1" \
	"Error: no exchange rate available before 2009-01-02 => 0000-02-29"
expect_line "February 28 of a common year" "2013-02-28 | 1" "2013-02-28 => 1 = 33.36"
expect_line "February 30 never exists" "2012-02-30 | 1" "Error: invalid date => 2012-02-30"
expect_line "February 31 never exists" "2012-02-31 | 1" "Error: invalid date => 2012-02-31"
expect_line "day after a leap day missing from the database" "2012-03-01 | 1" "2012-03-01 => 1 = 4.98"

echo "== Days in each month"
expect_line "January has 31 days" "2011-01-31 | 1" "2011-01-31 => 1 = 0.61"
expect_line "March has 31 days" "2011-03-31 | 1" "2011-03-31 => 1 = 0.8"
expect_line "May has 31 days" "2011-05-31 | 1" "2011-05-31 => 1 = 8.68"
expect_line "July has 31 days" "2011-07-31 | 1" "2011-07-31 => 1 = 14.06"
expect_line "August has 31 days" "2011-08-31 | 1" "2011-08-31 => 1 = 9.4"
expect_line "October has 31 days" "2011-10-31 | 1" "2011-10-31 => 1 = 3.38"
expect_line "December has 31 days" "2011-12-31 | 1" "2011-12-31 => 1 = 4.47"
expect_line "April has 30 days" "2011-04-30 | 1" "2011-04-30 => 1 = 2.66"
expect_line "June has 30 days" "2011-06-30 | 1" "2011-06-30 => 1 = 17.89"
expect_line "September has 30 days" "2011-09-30 | 1" "2011-09-30 => 1 = 4.95"
expect_line "November has 30 days" "2011-11-30 | 1" "2011-11-30 => 1 = 3"
expect_line "April 31" "2011-04-31 | 1" "Error: invalid date => 2011-04-31"
expect_line "June 31" "2011-06-31 | 1" "Error: invalid date => 2011-06-31"
expect_line "September 31" "2011-09-31 | 1" "Error: invalid date => 2011-09-31"
expect_line "November 31" "2011-11-31 | 1" "Error: invalid date => 2011-11-31"
expect_line "day 32" "2011-01-32 | 1" "Error: invalid date => 2011-01-32"
expect_line "day 32" "2011-12-32 | 1" "Error: invalid date => 2011-12-32"
expect_line "day 00" "2011-01-00 | 1" "Error: invalid date => 2011-01-00"
expect_line "day 99" "2011-01-99 | 1" "Error: invalid date => 2011-01-99"
expect_line "month 00" "2011-00-10 | 1" "Error: invalid date => 2011-00-10"
expect_line "month 13" "2011-13-01 | 1" "Error: invalid date => 2011-13-01"
expect_line "month 99" "2011-99-01 | 1" "Error: invalid date => 2011-99-01"

echo "== Date format"
expect_line "subject example, no value" "2001-42-42" "Error: bad input => 2001-42-42"
expect_line "month without leading zero" "2011-1-03 | 1" "Error: bad input => 2011-1-03 | 1"
expect_line "day without leading zero" "2011-01-3 | 1" "Error: bad input => 2011-01-3 | 1"
expect_line "neither" "2011-1-3 | 1" "Error: bad input => 2011-1-3 | 1"
expect_line "2-digit year" "11-01-03 | 1" "Error: bad input => 11-01-03 | 1"
expect_line "5-digit year" "20110-01-03 | 1" "Error: bad input => 20110-01-03 | 1"
expect_line "slashes" "2011/01/03 | 1" "Error: bad input => 2011/01/03 | 1"
expect_line "dots" "2011.01.03 | 1" "Error: bad input => 2011.01.03 | 1"
expect_line "spaces" "2011 01 03 | 1" "Error: bad input => 2011 01 03 | 1"
expect_line "day first" "03-01-2011 | 1" "Error: bad input => 03-01-2011 | 1"
expect_line "time after the date" "2011-01-03T00:00 | 1" "Error: bad input => 2011-01-03T00:00 | 1"
expect_line "negative year" "-2011-01-03 | 1" "Error: bad input => -2011-01-03 | 1"
expect_line "plus sign" "+2011-01-03 | 1" "Error: bad input => +2011-01-03 | 1"
expect_line "letter in the year" "201a-01-03 | 1" "Error: bad input => 201a-01-03 | 1"
expect_line "letter in the month" "2011-0a-03 | 1" "Error: bad input => 2011-0a-03 | 1"
expect_line "letter in the day" "2011-01-0a | 1" "Error: bad input => 2011-01-0a | 1"
expect_line "letters only" "abcd-ef-gh | 1" "Error: bad input => abcd-ef-gh | 1"
expect_line "space before the date" " 2011-01-03 | 1" "Error: bad input =>  2011-01-03 | 1"

echo "== Separator"
expect_line "no spaces" "2011-01-03|1" "Error: bad input => 2011-01-03|1"
expect_line "no space after |" "2011-01-03 |1" "Error: bad input => 2011-01-03 |1"
expect_line "no space before |" "2011-01-03| 1" "Error: bad input => 2011-01-03| 1"
expect_line "two spaces before |" "2011-01-03  | 1" "Error: bad input => 2011-01-03  | 1"
expect_line "two spaces after |" "2011-01-03 |  1" "Error: bad input => 2011-01-03 |  1"
expect_line "tabs" $'2011-01-03\t|\t1' $'Error: bad input => 2011-01-03\t|\t1'
expect_line "comma" "2011-01-03,1" "Error: bad input => 2011-01-03,1"
expect_line "comma with spaces" "2011-01-03 , 1" "Error: bad input => 2011-01-03 , 1"
expect_line "space only" "2011-01-03 1" "Error: bad input => 2011-01-03 1"
expect_line "double |" "2011-01-03 || 1" "Error: bad input => 2011-01-03 || 1"
expect_line "two separators" "2011-01-03 | 1 | 2" "Error: bad input => 2011-01-03 | 1 | 2"

echo "== Line shape"
expect_line "empty line" "" "Error: bad input => "
expect_line "spaces only" "   " "Error: bad input =>    "
expect_line "date only" "2011-01-03" "Error: bad input => 2011-01-03"
expect_line "no value" "2011-01-03 |" "Error: bad input => 2011-01-03 |"
expect_line "empty value" "2011-01-03 | " "Error: bad input => 2011-01-03 | "
expect_line "no date" "| 1" "Error: bad input => | 1"
expect_line "empty date" " | 1" "Error: bad input =>  | 1"
expect_line "separator only" " | " "Error: bad input =>  | "
expect_line "text" "hello world" "Error: bad input => hello world"

echo "== Values from 0 to 1000"
expect_line "integer" "2011-01-03 | 3" "2011-01-03 => 3 = 0.9"
expect_line "float" "2011-01-03 | 1.2" "2011-01-03 => 1.2 = 0.36"
expect_line "float below 1" "2011-01-03 | 0.5" "2011-01-03 => 0.5 = 0.15"
expect_line "0" "2011-01-03 | 0" "2011-01-03 => 0 = 0"
expect_line "0.0" "2011-01-03 | 0.0" "2011-01-03 => 0.0 = 0"
expect_line "+0" "2011-01-03 | +0" "2011-01-03 => +0 = 0"
expect_line "00" "2011-01-03 | 00" "2011-01-03 => 00 = 0"
expect_line "1000" "2011-01-03 | 1000" "2011-01-03 => 1000 = 300"
expect_line "1000.0" "2011-01-03 | 1000.0" "2011-01-03 => 1000.0 = 300"
expect_line "1000 with many zeros" "2011-01-03 | 1000.000000000000000000" "2011-01-03 => 1000.000000000000000000 = 300"
expect_line "+1000" "2011-01-03 | +1000" "2011-01-03 => +1000 = 300"
expect_line "1000 with leading zeros" "2011-01-03 | 0001000" "2011-01-03 => 0001000 = 300"
expect_line "just below 1000" "2011-01-03 | 999.999" "2011-01-03 => 999.999 = 299.9997"
expect_line "plus sign" "2011-01-03 | +5" "2011-01-03 => +5 = 1.5"
expect_line "leading zeros" "2011-01-03 | 007" "2011-01-03 => 007 = 2.1"
expect_line "leading and trailing zeros" "2011-01-03 | 0001.5000" "2011-01-03 => 0001.5000 = 0.45"

echo "== Negative values"
expect_line "subject example" "2012-01-11 | -1" "Error: not a positive number."
expect_line "-0" "2011-01-03 | -0" "Error: not a positive number."
expect_line "-0.0" "2011-01-03 | -0.0" "Error: not a positive number."
expect_line "-0.5" "2011-01-03 | -0.5" "Error: not a positive number."
expect_line "-1000" "2011-01-03 | -1000" "Error: not a positive number."
expect_line "-1001" "2011-01-03 | -1001" "Error: not a positive number."
expect_line "below INT_MIN" "2011-01-03 | -2147483649" "Error: not a positive number."
expect_line "huge negative" "2011-01-03 | -99999999999999999999999" "Error: not a positive number."

echo "== Values above 1000"
expect_line "subject example" "2012-01-11 | 2147483648" "Error: too large a number."
expect_line "1001" "2011-01-03 | 1001" "Error: too large a number."
expect_line "1000.0001" "2011-01-03 | 1000.0001" "Error: too large a number."
expect_line "rounds to exactly 1000 as a double" "2011-01-03 | 1000.0000000000000001" "Error: too large a number."
expect_line "+1001" "2011-01-03 | +1001" "Error: too large a number."
expect_line "1001 with a leading zero" "2011-01-03 | 01001" "Error: too large a number."
expect_line "10000" "2011-01-03 | 10000" "Error: too large a number."
expect_line "huge" "2011-01-03 | 99999999999999999999999" "Error: too large a number."
HUGE_VALUE="1$(printf '%400s' "" | tr ' ' '0')"
expect_line "too large for a double" "2011-01-03 | $HUGE_VALUE" "Error: too large a number."

echo "== Values that are not numbers"
for value in ".5" "5." "1.2.3" "1..2" "1e3" "1E3" "1e-3" "0x10" "nan" "NaN" "inf" "+inf" "-inf" "infinity" \
	"1,5" "1 000" "1f" "1.5f" "abc" "1abc" "abc1" "+" "-" "++1" "+-1" "-+1" "--1" "1+" "1-" "+.5" "-.5" "1 " "٣"; do
	expect_line "not a number" "2011-01-03 | $value" "Error: bad input => 2011-01-03 | $value"
done

echo "== Order of the checks"
expect_line "bad value format before invalid date" "2013-02-29 | abc" "Error: bad input => 2013-02-29 | abc"
expect_line "invalid date before negative value" "2013-02-29 | -1" "Error: invalid date => 2013-02-29"
expect_line "invalid date before too large value" "2013-02-29 | 2000" "Error: invalid date => 2013-02-29"
expect_line "negative value before missing rate" "2009-01-01 | -1" "Error: not a positive number."
expect_line "too large value before missing rate" "2009-01-01 | 2000" "Error: too large a number."

echo "== Exchange rate lookup"
expect_line "date in the database" "2011-01-01 | 1" "2011-01-01 => 1 = 0.3"
expect_line "missing date: lower 2011-01-07 (0.32), not the closer 2011-01-10 (0.33)" "2011-01-09 | 1" \
	"2011-01-09 => 1 = 0.32"
expect_line "the upper date itself" "2011-01-10 | 1" "2011-01-10 => 1 = 0.33"
expect_line "first date of the database" "2009-01-02 | 1" "2009-01-02 => 1 = 0"
expect_line "day before the first date" "2009-01-01 | 1" \
	"Error: no exchange rate available before 2009-01-02 => 2009-01-01"
expect_line "year 0000" "0000-01-01 | 1" "Error: no exchange rate available before 2009-01-02 => 0000-01-01"
expect_line "last date of the database" "2022-03-29 | 1" "2022-03-29 => 1 = 47115.93"
expect_line "day after the last date" "2022-03-30 | 1" "2022-03-30 => 1 = 47115.93"
expect_line "far future" "9999-12-31 | 1" "9999-12-31 => 1 = 47115.93"
expect_line "rate of 0" "2010-08-17 | 5" "2010-08-17 => 5 = 0"

echo "== Result format"
expect_line "large result, no scientific notation" "2022-03-29 | 1000" "2022-03-29 => 1000 = 47115930"
expect_line "large result with decimals" "2022-03-29 | 999.99" "2022-03-29 => 999.99 = 47115458.84"
expect_line "small result" "2011-01-03 | 0.001" "2011-01-03 => 0.001 = 0.0003"
expect_line "tiny value" "2022-03-29 | 0.000001" "2022-03-29 => 0.000001 = 0.04711593"
expect_line "0.3 * 3 shows 0.9, not 0.8999999999999999" "2011-01-03 | 3" "2011-01-03 => 3 = 0.9"

echo "== Database (data.csv)"
mkdir "$TMP/no_database"
run "$TMP/no_database" "$PWD/input.txt"
check "data.csv missing" 1 "" "Error: could not open database data.csv."
run "$TMP/no_database" does_not_exist.txt
check "data.csv and input file both missing: database first" 1 "" "Error: could not open database data.csv."
mkdir -p "$TMP/database_directory/data.csv"
run "$TMP/database_directory" "$PWD/input.txt"
accept_directory_as_empty_on_macos "Error: database data.csv has no exchange rates." \
	"Error: could not read database data.csv."
check "data.csv is a directory" 1 "" "Error: could not read database data.csv."
INPUT=$'date | value\n2011-01-05 | 1\n'
expect_database "empty data.csv" "" "$INPUT" 1 "" "Error: database data.csv has no exchange rates."
expect_database "header only" $'date,exchange_rate\n' "$INPUT" 1 "" "Error: database data.csv has no exchange rates."
expect_database "no header" $'2011-01-01,2\n' "$INPUT" 0 "2011-01-05 => 1 = 2" ""
expect_database "other header is a bad line" $'Date,Rate\n2011-01-01,2\n' "$INPUT" 1 "" \
	"Error: data.csv line 1: invalid date => Date,Rate"
expect_database "byte order mark before the header" $'\xEF\xBB\xBFdate,exchange_rate\n2011-01-01,2\n' "$INPUT" 0 \
	"2011-01-05 => 1 = 2" ""
expect_database "Windows line endings (CRLF)" $'date,exchange_rate\r\n2011-01-01,2\r\n' "$INPUT" 0 \
	"2011-01-05 => 1 = 2" ""
expect_database "no newline at the end" $'date,exchange_rate\n2011-01-01,2' "$INPUT" 0 "2011-01-05 => 1 = 2" ""
expect_database "decimal rate" $'date,exchange_rate\n2011-01-01,0.25\n' "$INPUT" 0 "2011-01-05 => 1 = 0.25" ""
expect_database "rate of 0" $'date,exchange_rate\n2011-01-01,0\n' "$INPUT" 0 "2011-01-05 => 1 = 0" ""
expect_database "dates out of order" $'date,exchange_rate\n2011-01-10,3\n2011-01-01,2\n' \
	$'2011-01-05 | 1\n2011-01-10 | 1\n' 0 $'2011-01-05 => 1 = 2\n2011-01-10 => 1 = 3' ""
expect_database "lower date used even when the upper one is closer" $'date,exchange_rate\n2011-01-01,1\n2011-01-10,2\n' \
	$'2011-01-09 | 1\n2011-01-10 | 1\n2011-01-11 | 1\n2010-12-31 | 1\n' 0 \
	$'2011-01-09 => 1 = 1\n2011-01-10 => 1 = 2\n2011-01-11 => 1 = 2\nError: no exchange rate available before 2011-01-01 => 2010-12-31' ""
expect_database "February 29 of a leap year" $'date,exchange_rate\n2012-02-29,5\n' $'2012-03-01 | 1\n' 0 \
	"2012-03-01 => 1 = 5" ""
database_error "date with a bad format" "2011-1-05,2" "invalid date"
database_error "February 29 of a common year" "2013-02-29,2" "invalid date"
database_error "February 29 of a century not divisible by 400" "2100-02-29,2" "invalid date"
database_error "April 31" "2011-04-31,2" "invalid date"
database_error "month 13" "2011-13-01,2" "invalid date"
database_error "day 00" "2011-01-00,2" "invalid date"
database_error "space before the comma" "2011-01-05 ,2" "invalid date"
database_error "header again" "date,exchange_rate" "invalid date"
database_error "negative rate" "2011-01-05,-2" "invalid exchange rate"
database_error "rate with a plus sign" "2011-01-05,+2" "invalid exchange rate"
database_error "empty rate" "2011-01-05," "invalid exchange rate"
database_error "letters" "2011-01-05,abc" "invalid exchange rate"
database_error "space after the comma" "2011-01-05, 2" "invalid exchange rate"
database_error "two commas" "2011-01-05,2,3" "invalid exchange rate"
database_error ".5" "2011-01-05,.5" "invalid exchange rate"
database_error "1e3" "2011-01-05,1e3" "invalid exchange rate"
database_error "inf" "2011-01-05,inf" "invalid exchange rate"
database_error "nan" "2011-01-05,nan" "invalid exchange rate"
database_error "rate too large for a double" "2011-01-05,$HUGE_VALUE" "exchange rate too large"
database_error "no comma" "2011-01-05 2" 'expected "date,exchange_rate"'
database_error "empty line" "" 'expected "date,exchange_rate"'
database_error "duplicate date" "2011-01-01,3" "duplicate date"

echo "== Every date of data.csv"
# Each line of data.csv becomes an input line "date | rate": every date has an exact match, so each line
# prints rate * rate, or "too large a number" once the rate is above 1000 (from 2017 on). Printed with
# 10 significant digits, like btc.
sed '1s/^date,exchange_rate$/date | value/; 1!s/,/ | /' data.csv > "$TMP/every_date.txt"
EXPECTED=$(awk -F, 'NR > 1 {
	if ($2 + 0 > 1000) print "Error: too large a number."
	else printf "%s => %s = %.10g\n", $1, $2, $2 * $2
}' data.csv)
run . "$TMP/every_date.txt"
check "./btc on all $(($(wc -l < data.csv) - 1)) dates of data.csv" 0 "$EXPECTED" ""

echo "== Memory (valgrind)"
if command -v valgrind > /dev/null 2>&1; then
	for case in "input.txt" "edge_cases.txt" "does_not_exist.txt" "$TMP" ""; do
		(valgrind -q --leak-check=full --error-exitcode=42 "$BTC" $case > /dev/null 2> "$TMP/valgrind")
		STATUS=$?
		STDOUT=""
		STDERR=$(grep '^==[0-9]*==' "$TMP/valgrind")
		[ "$STATUS" -ne 42 ] && STATUS=0
		check "no leak or memory error: ./btc $case" 0 "" ""
	done
	(cd "$TMP/database" && valgrind -q --leak-check=full --error-exitcode=42 "$BTC" "$TMP/input.txt" > /dev/null 2> "$TMP/valgrind")
	STATUS=$?
	STDOUT=""
	STDERR=$(grep '^==[0-9]*==' "$TMP/valgrind")
	[ "$STATUS" -ne 42 ] && STATUS=0
	check "no leak or memory error: invalid database" 0 "" ""
else
	echo "--  skipped: valgrind is not installed"
fi

echo "== $PASSED passed, $FAILED failed"
[ "$FAILED" -eq 0 ]
