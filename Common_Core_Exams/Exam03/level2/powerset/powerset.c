#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s n elem1 elem2 ... elemK\n", argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);
	int no_nums = argc - 2;

	// Convert string containing numbers to int array
	int *s = malloc(no_nums * sizeof(int));
	if (!s) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}
	for (int i = 0; i < no_nums; i++) {
		s[i] = atoi(argv[i + 2]);
	}

	/* Enumerate all subsets. Max amount: 2^no_nums
	 * Uses a mask to represent the current number permutation
	 * Each bit in the mask corresponds to an element in s
	 * 1 means include, 0 means exclude.
	 */
	for (unsigned long long mask = 0; mask < 1ULL << no_nums; mask++) {
		int sum = 0;

		/* Check each bit of the mask: if bit i is 1, include s[i] in the sum.
		 * Each bit in 'mask' corresponds to an index in 's':
		 * - bit i = 1 -> include s[i] in the sum
		 * - bit i = 0 -> exclude s[i]
		 * The mask’s numeric value is the sum of 2^i for all included indices,
		 * which is why (mask & (1ULL << i)) checks if s[i] should be included.
		 */
		for (int i = 0; i < no_nums; i++) {
			if (mask & 1ULL << i)
				sum += s[i];
		}

		// If current number permutation is valid (is the sum), print it
		if (sum == n) {
			int first = 1;
			/* Prints the numbers used in the current subset by using the
			 * same mask logic as above, but instead of checking if it should
			 * be included in the sum, it prints the number if included.
			 * 'first' flag is used to manage spaces between numbers.
			 */
			for (int i = 0; i < no_nums; i++) {
				if (mask & 1ULL << i) {
					if (!first)
						printf(" ");
					printf("%d", s[i]);
					first = 0;
				}
			}
			printf("\n");
		}
	}
	free(s);
	return 0;
}
