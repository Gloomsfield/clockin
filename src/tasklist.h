#pragma once

#include "config.h"
#include "task.h"
#include "status.h"

typedef struct tasklist_t {
	task_t* tasks;
	uint32_t capacity;
	uint32_t count;
} tasklist_t;

typedef struct clockin_state_t clockin_state_t;
clockin_status_t new_tasklist(clockin_config_t config, tasklist_t** tasklist);

clockin_status_t write_tasks(tasklist_t* buffer, char* out, uint32_t length);

void free_tasklist(tasklist_t** tasklist);

