#pragma once

#include "backend-typedefs.h"
#include "status.h"

struct task_t {
	char* description;
};

clockin_status_t new_task(clockin_config_t config, task_t* task);

void free_task(task_t** task);

