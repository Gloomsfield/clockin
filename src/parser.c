#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

clockin_status_t read_tasks_for_guild(char* task_directory_path, uint64_t guild_id, task_buffer_t* task_buffer) {
	char guild_path[24] = { '\0' };
	snprintf(guild_path, 23, "%lu.txt", guild_id);

	FILE* task_file = fopen(guild_path, "r");

	if(!task_file) { return CLOCKIN_TASK_FILE_READ_FAIL; }

	const int line_buffer_length = 512;
	char* line_buffer = calloc(line_buffer_length, sizeof(char));

	uint32_t task_index = 0;

	while(fgets(line_buffer, line_buffer_length, task_file))  {
		strcpy(task_buffer->tasks[task_index].description, line_buffer);

		task_index++;
	}

	task_buffer->count = task_index;

	fclose(task_file);

	free(line_buffer);

	return CLOCKIN_SUCCESS;
}

