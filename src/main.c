#include "../include/text_utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *input = stdin;

	if (argc == 1) {
		printf("usage: sform <file>\n");
		return 1;
	}

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "err: could not open file %s\n", argv[1]);
			return 1;
		}
	}

	wrap_text(input, stdout, DEFAULT_WIDTH);

	if (input != stdin)
		fclose(input);

	return 0;
}