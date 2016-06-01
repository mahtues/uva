#include <stdio.h>
#include <string.h>

#include <math.h>
#include <crypt.h>

#define N_MAX 1000000

typedef struct {
	int a[3][3];
} matrix_3_3_t;

typedef struct {
	int a[3][1];
} matrix_3_1_t;

int matrix_3_1_print(matrix_3_1_t a)
{
	printf("{\n  %d\n  %d\n  %d\n}\n", a.a[0][0], a.a[1][0], a.a[2][0]);

	return 0;
}

matrix_3_1_t matrix_3_3_dot_3_1(matrix_3_3_t a, matrix_3_1_t b)
{
	matrix_3_1_t c;

	c.a[0][0] = a.a[0][0] * b.a[0][0] + a.a[0][1] * b.a[1][0] + a.a[0][2] * b.a[2][0];
	c.a[1][0] = a.a[1][0] * b.a[0][0] + a.a[1][1] * b.a[1][0] + a.a[1][2] * b.a[2][0];
	c.a[2][0] = a.a[2][0] * b.a[0][0] + a.a[2][1] * b.a[1][0] + a.a[2][2] * b.a[2][0];

	return c;
}

matrix_3_3_t A = {.a = {{1, -2, 2}, {2, -1, 2}, {2, -2, 3}}};
matrix_3_3_t B = {.a = {{1, 2, 2}, {2, 1, 2}, {2, 2, 3}}};
matrix_3_3_t C = {.a = {{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}}};
matrix_3_1_t root = {.a = {{3}, {4}, {5}}};

int N;
int n_triples;
int in_triple[N_MAX];
int n_in_triple;

int do_magic(matrix_3_1_t root)
{
	int h;
	int m;
	int t;

	h = root.a[0][0];
	h = h > root.a[1][0] ? h : root.a[1][0];
	h = h > root.a[2][0] ? h : root.a[2][0];

	if (h > N) {
		return 0;
	}

	n_triples++;

	for (m = N / h; m > 0; m--) {
		t = root.a[0][0] * m;
		n_in_triple += (1 - in_triple[t]);
		in_triple[t] = 1;

		t = root.a[1][0] * m;
		n_in_triple += (1 - in_triple[t]);
		in_triple[t] = 1;

		t = root.a[2][0] * m;
		n_in_triple += (1 - in_triple[t]);
		in_triple[t] = 1;
	}

	do_magic(matrix_3_3_dot_3_1(A, root));
	do_magic(matrix_3_3_dot_3_1(B, root));
	do_magic(matrix_3_3_dot_3_1(C, root));

	return 0;
}

int main(long long int argc, char **argv)
{
	char input_line[1024];

	while (fgets(input_line, 1024, stdin)) {
		sscanf(input_line, "%d", &N);
		memset(in_triple, 0, sizeof(in_triple));
		n_triples = 0;
		n_in_triple = 0;

		do_magic(root);

		printf("%d %d\n", n_triples, N - n_in_triple);
	}

	return 0;
}

