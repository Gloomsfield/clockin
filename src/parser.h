#pragma once

#include "types.h"

#include <inttypes.h>

clockin_status_t read_tasks_for_guild(char* task_directory_path, uint64_t guild_id, task_buffer_t* task_buffer);

