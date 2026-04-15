#include "state.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

clockin_status_t new_state(clockin_config_t config, clockin_state_t** state) {
	clockin_state_t new_state = { 0 };

	clockin_config_t* config_ptr = calloc(1, sizeof(clockin_config_t));
	memcpy(config_ptr, &config, sizeof(clockin_config_t));

	new_state.config = config_ptr;

	new_state.guild_ids = calloc(new_state.config->guild_capacity, sizeof(uint64_t));
	new_state.tasklists = calloc(new_state.config->guild_capacity, sizeof(tasklist_t*));

	for(uint32_t i = 0; i < new_state.config->guild_capacity; i++) {
		new_state.tasklists[i] = calloc(1, sizeof(tasklist_t));

		clockin_status_t res = new_tasklist(
			*(new_state.config),
			&(new_state.tasklists[i])
		);

		if(res != CLOCKIN_SUCCESS) { return res; }
	}

	memcpy(*state, &new_state, sizeof(clockin_state_t));

	return CLOCKIN_SUCCESS;
}

void free_state(clockin_state_t** state) {
	free((*state)->config);
	(*state)->config = NULL;

	free((*state)->guild_ids);
	(*state)->guild_ids = NULL;

	for(uint32_t i = 0; i < (*state)->config->guild_capacity; i++) {
		free_tasklist(&(*state)->tasklists[i]);
		(*state)->tasklists[i] = NULL;
	}

	free((*state)->tasklists);
	(*state)->tasklists = NULL;

	free(*state);
	*state = NULL;
}

