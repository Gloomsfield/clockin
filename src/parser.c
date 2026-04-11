#include "parser.h"

#include <stdlib.h>
#include <string.h>

typedef enum {
	CLOCKIN_PARSE_TASK_READ,
	CLOCKIN_PARSE_TAG_READ,
} clockin_parse_state;

// the worst code i've ever written
// TODO - geez
clockin_status_t parse_tasks_from_file(char* path, task_buffer_t task_buffer) {
	FILE* task_file = fopen(path, "r");

	if(!task_file) { return CLOCKIN_TASK_FILE_READ_FAIL; }

	const int line_buffer_length = 512;
	char* line_buffer = calloc(line_buffer_length, sizeof(char));

	const int description_buffer_length = 512;
	char* description_buffer = calloc(description_buffer_length, sizeof(char));

	uint32_t task_index = 0;

	while(fgets(line_buffer, line_buffer_length, task_file))  {
		clockin_parse_state current_state = CLOCKIN_PARSE_TASK_READ;

		uint32_t c_index = 0;
		uint32_t c_index_offset = 0;
		char c = line_buffer[c_index];

		uint32_t tag_index = 0;

		while(c != '\0') {
			if(c == '|') {
				if(current_state == CLOCKIN_PARSE_TAG_READ) {
					task_buffer.tasks[task_index].tags[tag_index][c_index - c_index_offset] = '\0';

					tag_index++;
				} else if(current_state == CLOCKIN_PARSE_TASK_READ) {
					description_buffer[c_index] = '\0';
				}

				c_index++;
				c_index_offset = c_index;

				current_state = CLOCKIN_PARSE_TAG_READ;

				continue;
			}

			if(current_state == CLOCKIN_PARSE_TASK_READ) {
				task_buffer.tasks[task_index].description[c_index - c_index_offset] = c;
			}

			if(current_state == CLOCKIN_PARSE_TAG_READ) {
				task_buffer.tasks[task_index].tags[tag_index][c_index - c_index_offset] = c;
			}

			c_index++;
		}

		if(tag_index > 0) {
			task_buffer.tasks[task_index].tags[tag_index - 1][c_index - c_index_offset] = '\0';
		}

		task_index++;
	}

	fclose(task_file);
}

