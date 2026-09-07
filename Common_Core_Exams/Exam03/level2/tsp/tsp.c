#include <stdio.h>
#include <math.h> // for sqrtf()
#include <stdbool.h> // for bool type
// Allowed functions: write, sqrtf, getline, fseek, fscanf, ferror, feof,
// fabsf, memcpy, fprintf, fclose, malloc, calloc, realloc, free, fopen,
// errno, stderr, stdin, stdout

typedef struct {
	int		n;			/* total number of cities */
	int		path[11];	/* current partial permutation */
	bool	used[11];	/* Set used[i] to true if city i is already used */
	float	*x;			/* x-coordinates */
	float	*y;			/* y-coordinates */
	float	best_len;	/* best tour length found */
}	TSPState;

/* --------------------------------------------------------
 * Calculates the Euclidean distance between two cities
 * -------------------------------------------------------- */
static inline float dist(float *x, float *y, int a, int b) {
    float dx = x[a] - x[b];
    float dy = y[a] - y[b];
    return sqrtf(dx * dx + dy * dy);
}

// BACKTRACKING (branch-and-bound)
static void backtrack(TSPState *s, int level, float curr_len)
{
	/* --------------------------------------------------------
	 * GOAL STATE: full permutation formed
	 * -------------------------------------------------------- */
    if (level == s->n) {
		// Compute total length of a completed tour
        float total_len = curr_len + dist(s->x, s->y, s->path[s->n - 1], s->path[0]);

		// If better than best found, update best length
        if (total_len < s->best_len)
            s->best_len = total_len;
        return;
    }

    /* --------------------------------------------------------
     * TRY EACH UNUSED CITY AS NEXT CHOICE
     * -------------------------------------------------------- */
    for (int candidate_city = 1; candidate_city < s->n; candidate_city++) {

        // VALIDATION: skip used cities (To prevent inf loops and invalid permutations)
        if (s->used[candidate_city])
            continue;

    	/* --------------------------------------------------------
		 * IS_VALID: calculate new length and prune if exceeds best
		 * -------------------------------------------------------- */
        int prev_city = s->path[level - 1];

		// Add distance from previous city to current city with the current length
        float new_len = curr_len + dist(s->x, s->y, prev_city, candidate_city);

        // PRUNING: abandon paths that already exceed best since we only care about the best length
        if (new_len >= s->best_len)
            continue;

    	/* --------------------------------------------------------
		 * DO: choose/select city
		 * -------------------------------------------------------- */
        s->path[level] = candidate_city;
        s->used[candidate_city] = true;

		// Go further down the rabbit hole (state tree)
        backtrack(s, level + 1, new_len);

    	/* --------------------------------------------------------
		 * UNDO: unchoose/select city (backtrack)
		 * -------------------------------------------------------- */
        s->used[candidate_city] = false;
    }
}

/* ======================= Backtracking =======================
 * - Parsing: Lines 95-97
 * - Error Handling: Handled by fscanf & lines 100-104
 * - Initializing: Lines 109-121
 * - Goal State: Lines 32-40
 * - Make Choice: Lines 66-67
 * - Validation/Pruning: Lines 48-61
 * - Backtrack (Undo Choice): Lines 70 & 75
 * ============================================================
 */
int main(void)
{
    float x[11], y[11];
    int n = 0;

    /* Get input parsed as "%f, %f\n" */
    while (n < 11 && fscanf(stdin, "%f, %f", &x[n], &y[n]) == 2) {
    	n++;
	}

	/* Handle trivial cases */
	if (n < 2)
	{
		printf("0.00\n");
		return 0;
	}

    /* ------------------------------------------------------------
     * SOLVE_TSP SECTION
     * ------------------------------------------------------------ */
    TSPState s;
    s.n = n;
    s.x = x;
    s.y = y;
    s.best_len = 3.4e38f; // FLT_MAX alternative

    /* Pad used[] with 0 */
    for (int i = 0; i < n; i++)
        s.used[i] = false;

    /* Fix starting city to 0 */
    s.path[0] = 0;
    s.used[0] = true;

    backtrack(&s, 1, 0.0f);

	// Output the best length found as required
    fprintf(stdout, "%.2f\n", s.best_len);

    return 0;
}
