#pragma once

#include "backend-typedefs.h"
#include "config.h"
#include "status.h"
#include "tasklist.h"

#include <inttypes.h>

struct clockin_instance_t {
	clockin_config_t* config;
	
	tasklist_t** tasklists;
	uint64_t* guild_ids;

	uint32_t guild_count;
};

clockin_status_t new_instance(clockin_config_t config, clockin_instance_t** instance);

void free_instance(clockin_instance_t** instance);

