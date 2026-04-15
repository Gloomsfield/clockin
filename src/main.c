#include "config.h"
#include "parser.h"
#include "instance.h"

#include <concord/discord.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GUILD_ID
#error please build using a guild id!
#define GUILD_ID 0
#endif

#ifndef BOT_TOKEN
#error please build using a bot token!
#define BOT_TOKEN "aaaaaaaa"
#endif

void on_ready(struct discord* client, const struct discord_ready* event) {
	struct discord_create_guild_application_command clockin_tasks_params = {
		.name = "clockin-tasks",
		.description = "list tasks",
	};

	discord_create_guild_application_command(
		client,
		event->application->id,
		GUILD_ID,
		&clockin_tasks_params,
		NULL
	);
}

void on_interaction(struct discord* client, const struct discord_interaction* event) {
	if(event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
		return;
	}

	clockin_instance_t* clockin_instance = discord_get_data(client);

	if(strcmp(event->data->name, "clockin-tasks") == 0) {
		uint32_t guild_index = 0;

		for(guild_index = 0; guild_index < clockin_instance->guild_count; guild_index++) {
			if(event->guild_id == clockin_instance->guild_ids[guild_index]) { break; }
		}

		if(clockin_instance->guild_count <= guild_index) {
			populate_tasks_for_guild(clockin_instance, event->guild_id);
		}

		char* message = calloc(2048, sizeof(char));

		if(write_tasks(
			clockin_instance->tasklists[guild_index],
			message,
			2048
		) != CLOCKIN_SUCCESS) {
			return;
		}

		discord_create_interaction_response(
			client,
			event->id,
			event->token,
			&(struct discord_interaction_response) {
				.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
				.data = &(struct discord_interaction_callback_data) { .content = message, }
			},
			NULL
		);
	}
}

int main(int argc, const char* argv[]) {
	if(argc != 2) { exit(-2); }
	
	clockin_config_t config = {
		.task_directory = argv[1],
		.task_capacity = 512,
		.task_description_length = 512,
		.guild_capacity = 4,
	};

	clockin_instance_t* clockin_instance = calloc(1, sizeof(clockin_instance_t));

	if(new_instance(config, &clockin_instance) != CLOCKIN_SUCCESS) {
		exit(-3);
	}

	struct discord* client = discord_init(BOT_TOKEN);

	discord_set_data(client, clockin_instance);

	discord_set_on_ready(client, &on_ready);
	discord_set_on_interaction_create(client, &on_interaction);
	discord_run(client);
}

