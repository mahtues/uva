#include <stdio.h>

float max(float a, float b) {
	return ((a > b) ? a : b);
}

typedef struct _cell_t {
	float rate;
} cell_t;

int main(int argc, char **argv)
{
	char input[1024];
	int i, j, k;
	cell_t dist[20][20][20];
	int currencies = 0;
	char output[128] = "no arbitrage sequence exists";
	char buf[128] = "";
	void *dummy_ptr;

	while (fgets(input, 1024, stdin)) {
		sscanf(input, "%d", &currencies);

		for (k = 0; k < currencies; k++) {
			for (i = 0; i < currencies; i++) {
				for (j = 0; j < currencies; j++) {
					dist[k][i][j].rate = 1.0;
				}
			}
		}

		for (i = 0; i < currencies; i++) {
			dummy_ptr = fgets(input, 1024, stdin);
/*			sscanf(input, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", line+0, line+1, line+2, line+3, line+4, line+5, line+6, line+7, line+8, line+9, line+10, line+11, line+12, line+13, line+14, line+15, line+16, line+17, line+18); */
			sscanf(input, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &dist[0][i][i<=0?0+1:0].rate, &dist[0][i][i<=1?1+1:1].rate, &dist[0][i][i<=2?2+1:2].rate, &dist[0][i][i<=3?3+1:3].rate, &dist[0][i][i<=4?4+1:4].rate, &dist[0][i][i<=5?5+1:5].rate, &dist[0][i][i<=6?6+1:6].rate, &dist[0][i][i<=7?7+1:7].rate, &dist[0][i][i<=8?8+1:8].rate, &dist[0][i][i<=9?9+1:9].rate, &dist[0][i][i<=10?10+1:10].rate, &dist[0][i][i<=11?11+1:11].rate, &dist[0][i][i<=12?12+1:12].rate, &dist[0][i][i<=13?13+1:13].rate, &dist[0][i][i<=14?14+1:14].rate, &dist[0][i][i<=15?15+1:15].rate, &dist[0][i][i<=16?16+1:16].rate, &dist[0][i][i<=17?17+1:17].rate, &dist[0][i][i<=18?18+1:18].rate);
		}

		for (i = 0; i < currencies; i++) {
			for (j = 0; j < currencies; j++) {
				printf("%16.5f", dist[0][i][j].rate);
			}
			printf("\n");
		}
		printf("\n");

		for (k = 0; k < currencies; k++) {
			for (i = 0; i < currencies; i++) {
				for (j = 0; j < currencies; j++) {
					if (i != j && j != k && k != i) {
						dist[0][i][j].rate = max(dist[0][i][k].rate * dist[0][k][j].rate, dist[0][i][k].rate);
					}
				}
			}
		}

		sprintf(output, "no arbitrage sequence exists");
		
		for (i = 0; i < currencies; i++) {
			for (j = 0; j < currencies; j++) {
				printf("%16.5f", dist[0][i][j].rate);
			}
			printf("\n");
		}

		printf("\n%s\n\n", output);
	}
}
