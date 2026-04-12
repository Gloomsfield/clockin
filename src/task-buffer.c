#include "task-buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

clockin_status_t new_task_buffer(clockin_config_t config, task_buffer_t** buffer) {
	task_buffer_t new_buffer = { .capacity = config.guild_capacity, .count = 0, };

	new_buffer.tasks = calloc(new_buffer.capacity, sizeof(task_t));

	for(int i = 0; i < config.task_capacity; i++) {
		new_buffer.tasks[i] = (task_t){ 0 };

		clockin_status_t res = new_task(config, &(new_buffer.tasks[i]));

		if(res != CLOCKIN_SUCCESS) { return res; }
	}

	memcpy(*buffer, &new_buffer, sizeof(task_buffer_t));

	return CLOCKIN_SUCCESS;
}

clockin_status_t write_tasks(task_buffer_t* buffer, char* out, uint32_t length) {
	char* str = calloc(length, sizeof(char));

	uint32_t length_remaining = length;

	printf("%d\n", buffer->count);
	
	for(int i = 0; i < buffer->count; i++) {
		uint32_t description_length = strlen(buffer->tasks[i].description) + 1;

		if(length_remaining < description_length) {
			free(str);

			return CLOCKIN_PRINT_STRING_BUFFER_TOO_SMALL;
		}

		snprintf(
			&(str[length - length_remaining]),
			description_length,
			"%s\n", buffer->tasks[i].description
		);

		length_remaining -= description_length - 1;
	}

	strcpy(out, str);

	free(str);

	return CLOCKIN_SUCCESS;
}

void free_task_buffer(task_buffer_t** buffer) {
	for(uint32_t i = 0; i < (*buffer)->capacity; i++) {
		free_task(&(*buffer)->tasks);
		(*buffer)->tasks = NULL;
	}

	free(*buffer);
	*buffer = NULL;
}

