#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t EMPTY[] = {0, 0, 0, 0};

uint8_t FONTS[][4] = {
	{ 0b00100111, 0b01010111, 0b01110101, 0b01010101, },
	{ 0b01100111, 0b01010111, 0b01110101, 0b01110110, },
	{ 0b00110111, 0b01000100, 0b01000100, 0b01110011, },
	{ 0b01100111, 0b01010101, 0b01010101, 0b01110110, },
	{ 0b01110111, 0b01000110, 0b01100100, 0b01110111, },
	{ 0b01110111, 0b01000110, 0b01100100, 0b01000100, },
	{ 0b01110111, 0b01000100, 0b01110101, 0b01110011, },
	{ 0b01010101, 0b01010111, 0b01110101, 0b01010101, },
	{ 0b01110010, 0b00100010, 0b00100010, 0b00100111, },
	{ 0b00110001, 0b00010001, 0b00010101, 0b01110010, },
	{ 0b01010101, 0b01010110, 0b01100101, 0b01010101, },
	{ 0b01000100, 0b01000100, 0b01000100, 0b01110111, },
	{ 0b01010101, 0b01110111, 0b01010101, 0b01010101, },
	{ 0b01010101, 0b01110111, 0b01110111, 0b01010101, },
	{ 0b00100111, 0b01010101, 0b01010101, 0b01110010, },
	{ 0b01100111, 0b01010111, 0b01100100, 0b01000100, },
	{ 0b00100111, 0b01010101, 0b01010111, 0b01010011, },
	{ 0b01110101, 0b01010111, 0b01100101, 0b01010101, },
	{ 0b01110111, 0b01000010, 0b00100001, 0b01110111, },
	{ 0b01110111, 0b00100010, 0b00100010, 0b00100010, },
	{ 0b01010101, 0b01010101, 0b01010101, 0b01110111, },
	{ 0b01010101, 0b01010101, 0b01010111, 0b00100010, },
	{ 0b01010101, 0b01010101, 0b01110111, 0b01110101, },
	{ 0b01010101, 0b01010010, 0b00100101, 0b01010101, },
	{ 0b01010101, 0b01010101, 0b00100010, 0b00100010, },
	{ 0b01110001, 0b00010010, 0b00100010, 0b01000111, },
};

void rendering(char *buffer) {
	char *line_head = buffer;
	int is_head_of_line = 1;

	while (1) {
		char *line_cursor;

		// horizontal iteration
		for (int h = 0; h < 8; ++h) {
			int font_offset = 0;

			line_cursor = line_head;

			while (1) {
				char c = *line_cursor++;
				uint8_t (*glyph)[4] = &EMPTY;

				switch (c) {
					case 'A'...'Z': glyph = &FONTS[c - 'A']; break;
					case 'a'...'z': glyph = &FONTS[c - 'a']; break;
					case '\n':
					case '\r':
					case '\0':
						goto END_OF_LINE;
				}

				if (!is_head_of_line) printf("    ");
				int bitmap = (*glyph)[h >> 1] >> (!(h & 1) * 4);
				for (int i = 0; i < 3; ++i)
					printf(bitmap & (1 << (2 - i)) ? "fuck" : "    ");
				is_head_of_line = 0;
			}

END_OF_LINE:
			putchar('\n');
			is_head_of_line = 1;
		}


		line_cursor --;

		// if in end of buffer, return immediately
		if (*line_cursor == '\0') return;

		while (*line_cursor == '\r' || *line_cursor == '\n') {
			line_cursor++;

			// if in end of buffer, return immediately
			if (*line_cursor == '\0') return;
		}

		// set line_head to next line
		line_head = line_cursor;

		puts("");
		puts("");
	}

}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "%s [OUTPUT STIRNG]\n", argv[0]);
		exit(1);
	}

	rendering(argv[1]);
}
