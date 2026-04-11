#pragma once

#include "types.h"

#include <inttypes.h>

clockin_status_t read_tasks_for_guild(clockin_config_t* config, uint64_t guild_id, task_buffer_t* task_buffer);

