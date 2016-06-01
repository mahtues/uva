#include <stdio.h>
#include <string.h>

#define BROWN 0
#define GREEN 1
#define CLEAR 2

typedef struct _bin_t
{
	int brown;
	int green;
	int clear;
} bin_t;

typedef struct _answer_t
{
	char bin_seq[4];
	int movements;
} answer_t;

int main(int argc, char** argv)
{
	char input[128];
	bin_t bin[3];
	answer_t answer;
	int total;
	int movements;

	while (fgets(input, sizeof(input), stdin)) {
		sscanf(input, "%d %d %d %d %d %d %d %d %d", &bin[0].brown, &bin[0].green, &bin[0].clear, &bin[1].brown, &bin[1].green, &bin[1].clear, &bin[2].brown, &bin[2].green, &bin[2].clear);

		total = bin[0].brown + bin[0].green + bin[0].clear + bin[1].brown + bin[1].green + bin[1].clear + bin[2].brown + bin[2].green + bin[2].clear;

		/* 1. BCG */
		movements = total - (bin[0].brown + bin[1].clear + bin[2].green);
		{
			answer.movements = movements;
			strcpy(answer.bin_seq, "BCG");
		}

		/* 2. BGC */
		movements = total - (bin[0].brown + bin[1].green + bin[2].clear);
		if (movements < answer.movements) {
			answer.movements = movements;
			strcpy(answer.bin_seq, "BGC");
		}

		/* 3. CBG */
		movements = total - (bin[0].clear + bin[1].brown + bin[2].green);
		if (movements < answer.movements) {
			answer.movements = movements;
			strcpy(answer.bin_seq, "CBG");
		}

		/* 4. CGB */
		movements = total - (bin[0].clear + bin[1].green + bin[2].brown);
		if (movements < answer.movements) {
			answer.movements = movements;
			strcpy(answer.bin_seq, "CGB");
		}

		/* 5. GBC */
		movements = total - (bin[0].green + bin[1].brown + bin[2].clear);
		if (movements < answer.movements) {
			answer.movements = movements;
			strcpy(answer.bin_seq, "GBC");
		}

		/* 6. GCB */
		movements = total - (bin[0].green + bin[1].clear + bin[2].brown);
		if (movements < answer.movements) {
			answer.movements = movements;
			strcpy(answer.bin_seq, "GCB");
		}

		printf("%s %d\n", answer.bin_seq, answer.movements);
	}
}
