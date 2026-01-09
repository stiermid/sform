#include "../include/text_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage: sfrom <filename>\n");
		return 0;
	}

	char *filename = argv[1];

	// Create a temporary filename (e.g., "note.txt" -> "note.txt.tmp")
	// Allocate space for: length of filename + ".tmp" + null terminator
	char *temp_filename = malloc(strlen(filename) + 5);
	if (!temp_filename) {
		fprintf(stderr, "err: memory allocation failed\n");
		return 1;
	}
	strcpy(temp_filename, filename);
	strcat(temp_filename, ".tmp");

	// Open Original for Reading
	FILE *input = fopen(filename, "r");
	if (!input) {
		fprintf(stderr, "err: could not open file %s\n", filename);
		free(temp_filename);
		return 1;
	}

	// Open Temp for Writing
	FILE *output = fopen(temp_filename, "w");
	if (!output) {
		fprintf(stderr, "err: could not create temp file\n");
		fclose(input);
		free(temp_filename);
		return 1;
	}

	// Perform the formatting logic
	wrap_text(input, output, DEFAULT_WIDTH);

	// Close files to flush buffers
	fclose(input);
	fclose(output);

	// 3. The Swap (Delete original, Rename temp)
	if (remove(filename) != 0) {
		fprintf(stderr, "err: could not delete original file\n");
		remove(temp_filename);
		free(temp_filename);
		return 1;
	}

	if (rename(temp_filename, filename) != 0) {
		fprintf(stderr, "err: could not rename temp file to original\n");
		free(temp_filename);
		return 1;
	}

	// Cleanup memory
	free(temp_filename);

	printf("Successfully formatted: %s\n", filename);
	return 0;
}