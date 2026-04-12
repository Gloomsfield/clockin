#pragma once

#include "config.h"
#include "task.h"
#include "status.h"

typedef struct task_buffer_t {
	task_t** tasks;
	uint32_t capacity;
	uint32_t count;
} task_buffer_t;

typedef struct clockin_state_t clockin_state_t;
clockin_status_t new_task_buffer(clockin_config_t config, task_buffer_t** buffer);

void free_task_buffer(task_buffer_t** buffer);

