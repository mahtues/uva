#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cycle_of[1000001];

int calc_cycle(long long int n, int depth)
{
	int res;

	if (n == 1)
		return 1;

	if ((0 <= n) && (n <= 1000000)) {
		if (cycle_of[n] != 0) {
			return cycle_of[n];
		}
	}

	if ((n % 2) == 1)
		res = 1 + calc_cycle((n * 3 ) + 1, depth + 1);
	else
		res = 1 + calc_cycle(n / 2, depth + 1);

	if ((0 <= n) && (n <= 1000000)) {
		cycle_of[n] = res;
	}

	return res;
} 

int main(int argc, char** argv)
{
	int i;
	int n;
	char input[128];
	int in1, in2;
	int begin, end;
	int curr_cycle, max_cycle;

	memset(cycle_of, 0, sizeof(cycle_of));

	while (fgets(input, 128, stdin)) {
		sscanf(input, "%d %d", &in1, &in2);

		if (in1 < in2) {
			begin = in1;
			end = in2;
		} else {
			begin = in2;
			end = in1;
		}
		
		max_cycle = 0;
		for (i = begin; i <= end; i++) {
			curr_cycle = calc_cycle(i, 1);

			if (curr_cycle > max_cycle) {
				max_cycle = curr_cycle;
			}
			printf("%d %d %d\n", in1, in2, curr_cycle);
		}

	}

	return EXIT_SUCCESS;
}
