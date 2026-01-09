#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <stdio.h>

#define DEFAULT_WIDTH 80

void wrap_text(FILE *input_stream, FILE *output_stream, int max_line_length);

#endif
