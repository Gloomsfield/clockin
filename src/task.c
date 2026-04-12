#include "task.h"

#include "config.h"

#include <stdlib.h>
#include <string.h>

clockin_status_t new_task(clockin_config_t config, task_t* task) {
	task_t new_task = { 0 };

	new_task.description = calloc(config.task_description_length, sizeof(char));

	memcpy(task, &new_task, sizeof(task_t));

	return CLOCKIN_SUCCESS;
}

void free_task(task_t ** task) {
	free((*task)->description);
	(*task)->description = NULL;

	free(*task);
	*task = NULL;
}

