#pragma once

#include "config.h"
#include "status.h"
#include "tasklist.h"

#include <inttypes.h>

typedef struct clockin_state_t {
	clockin_config_t* config;
	
	tasklist_t** tasklists;
	uint64_t* guild_ids;

	uint32_t guild_count;
} clockin_state_t;

clockin_status_t new_state(clockin_config_t config, clockin_state_t** state);

void free_state(clockin_state_t** state);

