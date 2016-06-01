#include <stdio.h>
#include <string.h>

typedef struct _currency_t {
	int name;
	int passed;
	struct _currency_t *next[19];
	int next_length;
	float rate[19];
} currency_t;

int do_magic(int first, currency_t *curr, char *output, float rate, int depth, float *best_rate, int *best_rate_depth, char* buf)
{
	int i;
	char *tmp_buf;

	if (depth >= *best_rate_depth) {
		return 0;
	}

	if (curr->passed && curr->name != first) {
		return 0;
	}

	tmp_buf = buf + strlen(buf);

	if (curr->passed && curr->name == first) {
		sprintf(tmp_buf, " %d", curr->name);
		if (rate > 1.01 && depth <= *best_rate_depth && rate > *best_rate) {
			*best_rate = rate;
			*best_rate_depth = depth;
			strcpy(output, buf+1);
		}
		return 0;
	}

	curr->passed = 1;

	for (i = 0; i < curr->next_length; i++) {
		sprintf(tmp_buf, " %d", curr->name);
		do_magic(first, curr->next[i], output, curr->rate[i] * rate, depth + 1, best_rate, best_rate_depth, buf);
		sprintf(tmp_buf, "");
	}

	curr->passed = 0;

	return 0;
}

int main(int argc, char **argv)
{
	char input[1024];
	currency_t currency[20];
	float *line;
	int i, j;
	int currencies = 0;
	int result[20];
	int result_length;
	int overwrite;
	float best_rate;
	int best_rate_depth;
	char output[128] = "no arbitrage sequence exists";
	char buf[128] = "";
	void *dummy_ptr;

	for (i = 0; i < 20; i++) {
		currency[i].name = i + 1;
		currency[i].passed = 0;
		for (j = 0; j < 19; j++) {
			if (j < i) {
				currency[i].next[j] = &currency[j];
			} else {
				currency[i].next[j] = &currency[j+1];
			}
		}
	}

	while (fgets(input, 1024, stdin)) {
		sscanf(input, "%d", &currencies);

		for (i = 0; i < currencies; i++) {
			dummy_ptr = fgets(input, 1024, stdin);
			line = currency[i].rate;
			currency[i].next_length = currencies - 1;
			sscanf(input, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", line+0, line+1, line+2, line+3, line+4, line+5, line+6, line+7, line+8, line+9, line+10, line+11, line+12, line+13, line+14, line+15, line+16, line+17, line+18);
		}

		result_length = 0;
		overwrite = 0;
		best_rate = 0;
		best_rate_depth = 20;
		sprintf(output, "no arbitrage sequence exists");

		for (i = 0; i < currencies; i++) {
			overwrite = do_magic(currency[i].name, &currency[i], output, 1.0, 0, &best_rate, &best_rate_depth, buf);
		}
		printf("%s\n", output);
	}
}
