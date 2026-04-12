#include "parser.h"

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

static clockin_state_t clockin_state;

void on_ready(struct discord* client, const struct discord_ready* event) {
	struct discord_create_guild_application_command clockin_tasks_params = {
		.name = "clockin-tasks",
		.description = "list tasks",
	};

	discord_create_guild_application_command(client, event->application->id, GUILD_ID, &clockin_tasks_params, NULL);
}

void on_interaction(struct discord* client, const struct discord_interaction* event) {
	if(event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
		return;
	}

	if(strcmp(event->data->name, "clockin-tasks") == 0) {
		char response_buffer[4096] = { '\0' };

		uint32_t response_buffer_index = 0;

		for(uint32_t i = 0; i < task_buffer.count; i++) {
			int byte_count = snprintf(&(response_buffer[response_buffer_index]), 1024 - response_buffer_index, "task: %s\n", task_buffer.tasks[i].description);
			response_buffer_index += byte_count;

			if(byte_count < 1){
				printf("error! writing to response buffer failed!");
				return;
			}
		}

		struct discord_interaction_response response_params = {
			.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
			.data = &(struct discord_interaction_callback_data) { .content = response_buffer, },
		};

		discord_create_interaction_response(client, event->id, event->token, &response_params, NULL);
	}
}

int main(int argc, const char* argv[]) {
	if(argc != 2) { exit(-2); }
	
	clockin_config_t config = {
		.task_directory = argv[1],
		.task_capacity = 512,
		.task_description_length = 512,
	};


}

int main2(int argc, const char* argv[]) {
	if(argc != 2) {
		printf("please pass clockin the path to your guild task directory.");
		exit(-1);
	}

	clockin_config_t config = {
		.task_directory = argv[1],
		.task_capacity = 512,
	};

	task_buffer_t task_buffer = {
		.capacity = 512,
		.count = 0,
	};

	task_t* task_memory = calloc(task_buffer.capacity, sizeof(task_t));
	task_buffer.tasks = task_memory;

	if(parse_tasks_from_file("./examples/tasks.txt", &task_buffer) != CLOCKIN_SUCCESS) {
		exit(-1);
	}

	struct discord* client = discord_init(BOT_TOKEN);
	discord_set_on_ready(client, &on_ready);
	discord_set_on_interaction_create(client, &on_interaction);
	discord_run(client);
}

