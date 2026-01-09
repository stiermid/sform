#include "../include/text_utils.h"
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 4096

void wrap_text(FILE *input_stream, FILE *output_stream, int max_line_length)
{
	char word[MAX_WORD_LEN];
	int current_line_len = 0;

	while (fscanf(input_stream, "%4095s", word) == 1) {
		int word_len = strlen(word);

		if (current_line_len == 0) {
			fprintf(output_stream, "%s", word);
			current_line_len += word_len;
		} else {
			if (current_line_len + 1 + word_len > max_line_length) {
				fprintf(output_stream, "\n%s", word);
				current_line_len = word_len;
			} else {
				fprintf(output_stream, " %s", word);
				current_line_len += (1 + word_len);
			}
		}
	}

	fprintf(output_stream, "\n");
}