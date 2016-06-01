#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char input[128];
	int left, height, right;
	int most_left = 10001, most_right = -1;
	int skyline[10001];
	int i;
	int first_print = 1;

	memset(skyline, 0, sizeof(skyline));

	while(fgets(input, 128, stdin)) {
		sscanf(input, "%d %d %d", &left, &height, &right);

		if (left < most_left) {
			most_left = left;
		}

		if (right > most_right) {
			most_right = right;
		}
		
		for (i = left; i < right; i++) {
			if (skyline[i] < height) {
				skyline[i] = height;
			}
		}
	}

	height = -1;

	for (i = most_left; i <= most_right; i++) {
		if (skyline[i] != height) {
			if (first_print) {
				printf("%d %d", i, skyline[i]);
				first_print = 0;
			} else {
				printf(" %d %d", i, skyline[i]);
			}
			height = skyline[i];
		}
	}

	printf("\n");
}
