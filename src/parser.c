#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUILD_ID_STRING_LENGTH 19

clockin_status_t populate_tasks_for_guild(clockin_instance_t* instance, uint64_t guild_id) {
	// directory path + guild id + ".txt" + '\0'
	uint32_t path_length = strlen(instance->config->task_directory) + GUILD_ID_STRING_LENGTH + 4 + 1;

	char* guild_path = calloc(
		path_length,
		sizeof(char)
	);

	sprintf(guild_path, "%s/%lu.txt", instance->config->task_directory, guild_id);

	// have to use append+ here in case the file doesn't exist
	FILE* task_file = fopen(guild_path, "a+");

	free(guild_path);

	if(!task_file) { return CLOCKIN_TASK_FILE_READ_FAIL; }

	char* line_buffer = calloc(instance->config->task_description_length + 1, sizeof(char));

	uint32_t guild_index = 0;

	while(instance->guild_ids[guild_index] != guild_id) {
		if(instance->guild_count <= guild_index) {
			if(guild_index > instance->config->guild_capacity) {
				return CLOCKIN_GUILD_CAPACITY_TOO_SMALL;
			}

			instance->guild_ids[guild_index] = guild_id;

			break;
		}

		guild_index++;
	}

	uint32_t task_index = 0;

	while(fgets(line_buffer, instance->config->task_description_length + 1, task_file)) {
		strcpy(
			instance->tasklists[guild_index]->tasks[task_index].description,
			line_buffer
		);

		instance->tasklists[guild_index]->count++;
		task_index++;
	}

	fclose(task_file);

	return CLOCKIN_SUCCESS;
}

