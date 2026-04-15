#include "instance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

clockin_status_t new_instance(clockin_config_t config, clockin_instance_t** instance) {
	clockin_instance_t new_instance = { 0 };

	clockin_config_t* config_ptr = calloc(1, sizeof(clockin_config_t));
	memcpy(config_ptr, &config, sizeof(clockin_config_t));

	new_instance.config = config_ptr;

	new_instance.guild_ids = calloc(new_instance.config->guild_capacity, sizeof(uint64_t));
	new_instance.tasklists = calloc(new_instance.config->guild_capacity, sizeof(tasklist_t*));

	for(uint32_t i = 0; i < new_instance.config->guild_capacity; i++) {
		new_instance.tasklists[i] = calloc(1, sizeof(tasklist_t));

		clockin_status_t res = new_tasklist(
			*(new_instance.config),
			&(new_instance.tasklists[i])
		);

		if(res != CLOCKIN_SUCCESS) { return res; }
	}

	memcpy(*instance, &new_instance, sizeof(clockin_instance_t));

	return CLOCKIN_SUCCESS;
}

void free_instance(clockin_instance_t** instance) {
	free((*instance)->config);
	(*instance)->config = NULL;

	free((*instance)->guild_ids);
	(*instance)->guild_ids = NULL;

	for(uint32_t i = 0; i < (*instance)->config->guild_capacity; i++) {
		free_tasklist(&(*instance)->tasklists[i]);
		(*instance)->tasklists[i] = NULL;
	}

	free((*instance)->tasklists);
	(*instance)->tasklists = NULL;

	free(*instance);
	*instance = NULL;
}

