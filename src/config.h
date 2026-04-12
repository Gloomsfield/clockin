#pragma once

#include <inttypes.h>

typedef struct clockin_config_t {
	const char* task_directory;

	const uint32_t task_capacity;

	const uint32_t task_description_length; // ?
	
	const uint32_t guild_capacity;
} clockin_config_t;

