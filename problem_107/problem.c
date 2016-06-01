#include <stdio.h>
#include <math.h>

#define DEBUG 0

int powi(int b, int e)
{
	double bd = b;
	double ed = e;

	return lrint(pow(bd, ed));
}

int logb(int b, int x)
{
	double bd = b;
	double xd = x;

	return lrint(log(xd)/log(bd));
}

int an(int a0, int num, int den, int n)
{
	double a0d = a0;
	double numd = num;
	double dend = den;
	double nd = n;

	return lrint(a0d * pow(numd/dend, nd));
}

int main(int argc, char **argv)
{
	char input_line[1024];
	int h0, cn_max;

	int N, n_max;

	int sum_cn_until_max_minus_1;
	int sum_hn_cn_until_max;

	int n_max_h, n_max_c;
	int n;

	int c0 = 1;

	while (fgets(input_line, 1024, stdin)) {
		sscanf(input_line, "%d %d", &h0, &cn_max);

		if (h0 == 0 && cn_max == 0) {
			return 0;
		}

		DEBUG && printf("input: %d %d\n", h0, cn_max);

		for (N = 1; N <= cn_max ; N++) {
			if (N == 1) {
				n_max_h = logb(N+1, h0);
				n_max_c = n_max_h;
			} else {
				n_max_h = logb(N+1, h0);
				n_max_c = logb(N, cn_max);
			}

			if (n_max_h != n_max_c) {
				continue;
			}

			if (h0 != powi(N+1, n_max_h)) {
				continue;
			}

			if (cn_max != powi(N, n_max_c)) {
				continue;
			}

			n_max = n_max_h;
			DEBUG && printf("n_max_h = logb(%d, %d) = %d\n", N+1, h0, n_max_h);
			DEBUG && printf("n_max_c = logb(%d, %d) = %d\n", N, cn_max, n_max_c); 
			DEBUG && printf("N = %d, n_max = %d\n", N, n_max);
			break;
		}

		sum_hn_cn_until_max = sum_cn_until_max_minus_1 = 0;

		for (n = 0; n <= n_max; n++) {
			sum_hn_cn_until_max += an(h0 * c0, N, N + 1, n);
			if (n <= n_max - 1) {
				sum_cn_until_max_minus_1 += an(c0, N, 1, n);
			}
		}

		DEBUG && printf("output: ");
		printf("%d %d\n", sum_cn_until_max_minus_1, sum_hn_cn_until_max);
		DEBUG && printf("--\n");
	}

	return 0;
}

