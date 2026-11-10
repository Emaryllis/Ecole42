#include "PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

static const char *const WHITESPACE = " \t\n\v\f\r";

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other): _vector(other._vector), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// Accepts digits with an optional leading '+', from 1 to INT_MAX. Leading zeros are fine ("007").
// 0 is rejected: the subject asks for positive integers, and positive means greater than 0.
static int parseNumber(const std::string &token) {
	std::size_t i = 0;
	if (token[i] == '+') {
		++i;
	}
	if (i == token.size()) {
		throw std::invalid_argument("not a number: " + token);
	}
	int number = 0;
	for (; i < token.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(token[i]))) {
			throw std::invalid_argument("not a positive integer: " + token);
		}
		const int digit = token[i] - '0';
		if (number > (std::numeric_limits<int>::max() - digit) / 10) {
			throw std::out_of_range("too large: " + token);
		}
		number = number * 10 + digit;
	}
	if (number == 0) {
		throw std::invalid_argument("not a positive integer: " + token);
	}
	return number;
}

// Each argument can hold one or several numbers separated by spaces: ./PmergeMe 3 5 9 or ./PmergeMe "3 5 9".
// Split by hand rather than with std::istringstream: its first use costs about 10 us of one-off locale
// setup, which would be charged to whichever container is timed first.
void PmergeMe::fillVector(const int argc, char **argv) {
	_vector.clear();
	for (int i = 1; i < argc; ++i) {
		const std::string argument(argv[i]);
		std::string::size_type start = argument.find_first_not_of(WHITESPACE);
		if (start == std::string::npos) {
			throw std::invalid_argument("empty argument");
		}
		while (start != std::string::npos) {
			const std::string::size_type end = argument.find_first_of(WHITESPACE, start);
			_vector.push_back(parseNumber(argument.substr(start, end - start)));
			start = argument.find_first_not_of(WHITESPACE, end);
		}
	}
}

void PmergeMe::fillDeque(const int argc, char **argv) {
	_deque.clear();
	for (int i = 1; i < argc; ++i) {
		const std::string argument(argv[i]);
		std::string::size_type start = argument.find_first_not_of(WHITESPACE);
		if (start == std::string::npos) {
			throw std::invalid_argument("empty argument");
		}
		while (start != std::string::npos) {
			const std::string::size_type end = argument.find_first_of(WHITESPACE, start);
			_deque.push_back(parseNumber(argument.substr(start, end - start)));
			start = argument.find_first_not_of(WHITESPACE, end);
		}
	}
}

/*
 * Ford-Johnson merge-insertion sort (TAOCP Vol. 3, 5.3.1).
 *
 * The container is seen as a row of "units" of unitSize consecutive elements. A unit is always moved as
 * a whole and its last element is its largest, so the last element is the unit's key. Units are paired
 * up and each pair becomes a single unit of the next recursion level (unitSize * 2): every b stays
 * glued to its a, which is how a b finds its a again after the recursion, even with duplicates.
 *
 * 1. Pair the units: in each pair the smaller unit (b) goes first, the larger (a) second.
 * 2. Recursively sort the pairs by their a.
 * 3. Main chain: b1 a1 a2 ... am. b1 goes in front for free: b1 <= a1 and a1 is the smallest a.
 * 4. Binary insert b2 ... bm, plus the unpaired unit when there is an odd number of units, in the
 *    Jacobsthal order b3 b2, b5 b4, b11 ... b6, b21 ... b12, ... Since b(k) <= a(k), only the part of
 *    the chain before a(k) is searched. The Jacobsthal order keeps that part at 2^n - 1 elements or
 *    less, so each insertion costs at most n comparisons.
 * 5. Rebuild the container in main chain order. Elements that do not fill a whole unit stay at the end:
 *    they belong to a lower level, which inserts them.
 */
void PmergeMe::sortVector(const std::size_t unitSize) {
	const std::size_t unitCount = _vector.size() / unitSize;
	if (unitCount < 2) {
		return;
	}
	const std::size_t pairCount = unitCount / 2;

	// 1. Pairs
	for (std::size_t pair = 0; pair < pairCount; ++pair) {
		const std::vector<int>::iterator b = _vector.begin() + 2 * pair * unitSize;
		const std::vector<int>::iterator a = b + unitSize;
		if (*(b + unitSize - 1) > *(a + unitSize - 1)) {
			std::swap_ranges(b, a, a);
		}
	}

	// 2. Recursion
	sortVector(unitSize * 2);

	// 3. Main chain, holding the offset of each unit's first element. b(k) is at 2(k - 1) * unitSize,
	//    a(k) right after it.
	std::vector<std::size_t> chain;
	chain.push_back(0);
	for (std::size_t pair = 0; pair < pairCount; ++pair) {
		chain.push_back((2 * pair + 1) * unitSize);
	}

	// 4. Insertion. bCount includes b1, and the unpaired unit as b(m + 1).
	const std::size_t bCount = pairCount + unitCount % 2;
	std::size_t previousJacobsthal = 1;
	std::size_t jacobsthal = 3;
	while (previousJacobsthal < bCount) {
		// Position of a(k), found by walking back from the end of the chain, then from a(k + 1): only a's and
		// the b's of the current group can sit after a(k), so the walk stays short. The unpaired unit has no
		// a and keeps the end of the chain as its bound.
		std::size_t aPosition = chain.size();
		for (std::size_t k = std::min(jacobsthal, bCount); k > previousJacobsthal; --k) {
			const std::size_t offset = 2 * (k - 1) * unitSize;
			const int key = _vector[offset + unitSize - 1];
			if (k <= pairCount) {
				--aPosition;
				while (chain[aPosition] != offset + unitSize) {
					--aPosition;
				}
			}

			// Binary search in [0, aPosition): compare the key with the middle unit and keep the half it
			// belongs to, until the range is empty. low is then the first unit with a greater key.
			std::size_t low = 0;
			std::size_t high = aPosition;
			while (low < high) {
				const std::size_t middle = low + (high - low) / 2;
				if (key < _vector[chain[middle] + unitSize - 1]) {
					high = middle;
				} else {
					low = middle + 1;
				}
			}
			chain.insert(chain.begin() + low, offset);
			++aPosition;
		}
		const std::size_t nextJacobsthal = jacobsthal + 2 * previousJacobsthal;
		previousJacobsthal = jacobsthal;
		jacobsthal = nextJacobsthal;
	}

	// 5. Rebuild
	std::vector<int> sorted;
	sorted.reserve(_vector.size());
	for (std::vector<std::size_t>::const_iterator it = chain.begin(); it != chain.end(); ++it) {
		sorted.insert(sorted.end(), _vector.begin() + *it, _vector.begin() + *it + unitSize);
	}
	sorted.insert(sorted.end(), _vector.begin() + unitCount * unitSize, _vector.end());
	_vector.swap(sorted);
}

// Same algorithm as sortVector, step by step, on std::deque.
void PmergeMe::sortDeque(const std::size_t unitSize) {
	const std::size_t unitCount = _deque.size() / unitSize;
	if (unitCount < 2) {
		return;
	}
	const std::size_t pairCount = unitCount / 2;

	// 1. Pairs
	for (std::size_t pair = 0; pair < pairCount; ++pair) {
		const std::deque<int>::iterator b = _deque.begin() + 2 * pair * unitSize;
		const std::deque<int>::iterator a = b + unitSize;
		if (*(b + unitSize - 1) > *(a + unitSize - 1)) {
			std::swap_ranges(b, a, a);
		}
	}

	// 2. Recursion
	sortDeque(unitSize * 2);

	// 3. Main chain
	std::deque<std::size_t> chain;
	chain.push_back(0);
	for (std::size_t pair = 0; pair < pairCount; ++pair) {
		chain.push_back((2 * pair + 1) * unitSize);
	}

	// 4. Insertion
	const std::size_t bCount = pairCount + unitCount % 2;
	std::size_t previousJacobsthal = 1;
	std::size_t jacobsthal = 3;
	while (previousJacobsthal < bCount) {
		// Position of a(k), found by walking back from the end of the chain, then from a(k + 1): only a's and
		// the b's of the current group can sit after a(k), so the walk stays short. The unpaired unit has no
		// a and keeps the end of the chain as its bound.
		std::size_t aPosition = chain.size();
		for (std::size_t k = std::min(jacobsthal, bCount); k > previousJacobsthal; --k) {
			const std::size_t offset = 2 * (k - 1) * unitSize;
			const int key = _deque[offset + unitSize - 1];
			if (k <= pairCount) {
				--aPosition;
				while (chain[aPosition] != offset + unitSize) {
					--aPosition;
				}
			}

			// Binary search in [0, aPosition): compare the key with the middle unit and keep the half it
			// belongs to, until the range is empty. low is then the first unit with a greater key.
			std::size_t low = 0;
			std::size_t high = aPosition;
			while (low < high) {
				const std::size_t middle = low + (high - low) / 2;
				if (key < _deque[chain[middle] + unitSize - 1]) {
					high = middle;
				} else {
					low = middle + 1;
				}
			}
			chain.insert(chain.begin() + low, offset);
			++aPosition;
		}
		const std::size_t nextJacobsthal = jacobsthal + 2 * previousJacobsthal;
		previousJacobsthal = jacobsthal;
		jacobsthal = nextJacobsthal;
	}

	// 5. Rebuild
	std::deque<int> sorted;
	for (std::deque<std::size_t>::const_iterator it = chain.begin(); it != chain.end(); ++it) {
		sorted.insert(sorted.end(), _deque.begin() + *it, _deque.begin() + *it + unitSize);
	}
	sorted.insert(sorted.end(), _deque.begin() + unitCount * unitSize, _deque.end());
	_deque.swap(sorted);
}

static void printSequence(const std::string &label, const std::vector<int> &sequence) {
	std::cout << label;
	for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;
}

static bool isSorted(const std::vector<int> &sequence) {
	for (std::size_t i = 1; i < sequence.size(); ++i) {
		if (sequence[i - 1] > sequence[i]) {
			return false;
		}
	}
	return true;
}

static double toMicroseconds(const std::clock_t ticks) {
	return static_cast<double>(ticks) * 1000000.0 / CLOCKS_PER_SEC;
}

// Each time covers reading the arguments into the container (data management) and sorting it.
// Printing "Before:" is left out of the std::vector time.
void PmergeMe::run(const int argc, char **argv) {
	std::clock_t start = std::clock();
	fillVector(argc, argv);
	const std::clock_t vectorFillTicks = std::clock() - start;

	printSequence("Before:", _vector);

	start = std::clock();
	sortVector(1);
	const std::clock_t vectorTicks = vectorFillTicks + (std::clock() - start);

	start = std::clock();
	fillDeque(argc, argv);
	sortDeque(1);
	const std::clock_t dequeTicks = std::clock() - start;

	// Only one sorted sequence is printed, so check (outside the timing) that both containers hold it.
	if (!isSorted(_vector) || _deque.size() != _vector.size() ||
	    !std::equal(_vector.begin(), _vector.end(), _deque.begin())) {
		throw std::logic_error("std::vector and std::deque results differ");
	}

	printSequence("After:", _vector);
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : "
			<< toMicroseconds(vectorTicks) << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque  : "
			<< toMicroseconds(dequeTicks) << " us" << std::endl;
}