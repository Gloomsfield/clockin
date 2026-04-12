#pragma once

#include "status.h"

typedef struct task_t {
	char* description;
} task_t;

typedef struct clockin_config_t clockin_config_t;
clockin_status_t new_task(clockin_config_t config, task_t* task);

void free_task(task_t** task);

