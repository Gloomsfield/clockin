#pragma once

#include "backend-typedefs.h"
#include "config.h"
#include "task.h"
#include "status.h"

struct tasklist_t {
	task_t* tasks;
	uint32_t capacity;
	uint32_t count;
};

clockin_status_t new_tasklist(clockin_config_t config, tasklist_t** tasklist);

clockin_status_t write_tasks(tasklist_t* buffer, char* out, uint32_t length);

void free_tasklist(tasklist_t** tasklist);

