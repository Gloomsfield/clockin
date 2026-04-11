#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUILD_ID_STRING_LENGTH 19

clockin_status_t read_tasks_for_guild(
	clockin_config_t* config,
	uint64_t guild_id,
	task_buffer_t* task_buffer
) {
	// directory path + guild id + ".txt" + '\0'
	uint32_t path_length = strlen(config->task_directory) + GUILD_ID_STRING_LENGTH + 4 + 1;

	char* guild_path = calloc(
		path_length,
		sizeof(char)
	);

	sprintf(guild_path, "%s/%lu.txt", config->task_directory, guild_id);

	FILE* task_file = fopen(guild_path, "r");

	free(guild_path);

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

