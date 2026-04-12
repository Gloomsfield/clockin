#include "task-buffer.h"

#include <stdlib.h>
#include <string.h>

clockin_status_t new_task_buffer(clockin_config_t config, task_buffer_t** buffer) {
	task_buffer_t new_buffer = { .capacity = config.guild_capacity, };

	for(int i = 0; i < config.task_capacity; i++) {
		clockin_status_t res = new_task(config, &(new_buffer.tasks[i]));

		if(res != CLOCKIN_SUCCESS) { return res; }
	}

	memcpy(*buffer, &new_buffer, sizeof(task_buffer_t));

	return CLOCKIN_SUCCESS;
}

void free_task_buffer(task_buffer_t** buffer) {
	for(uint32_t i = 0; i < (*buffer)->capacity; i++) {
		free_task(&(*buffer)->tasks[i]);
		(*buffer)->tasks[i] = NULL;
	}

	free(*buffer);
	*buffer = NULL;
}

