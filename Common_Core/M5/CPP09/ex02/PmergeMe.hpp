#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <cstddef>
#include <deque>
#include <vector>

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void run(int argc, char **argv);

private:
	// Binary insertion jumps to the middle of a range, so both containers need random access: a linked list
	// has none, and sets or maps would sort by themselves. std::vector keeps its elements in one contiguous
	// block, std::deque in a series of fixed-size blocks: the two times show what that difference costs.
	std::vector<int> _vector;
	std::deque<int> _deque;

	void fillVector(int argc, char **argv);
	void fillDeque(int argc, char **argv);

	// Ford-Johnson merge-insertion sort, written once per container as the subject advises.
	void sortVector(std::size_t unitSize);
	void sortDeque(std::size_t unitSize);
};

#endif
