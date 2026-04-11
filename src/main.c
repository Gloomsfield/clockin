#include <concord/discord.h>

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
	struct discord_create_guild_application_command ping_params = {
		.name = "ping",
		.description = "ping command!",
	};

	discord_create_guild_application_command(client, event->application->id, GUILD_ID, &ping_params, NULL);
}

void on_interaction(struct discord* client, const struct discord_interaction* event) {
	if(event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
		return;
	}

	if(strcmp(event->data->name, "clockin") == 0) {
		struct discord_interaction_response response_params = {
			.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
			.data = &(struct discord_interaction_callback_data) { .content = "pong!", },
		};

		discord_create_interaction_response(client, event->id, event->token, &response_params, NULL);
	}
}

int main() {
	struct discord* client = discord_init(BOT_TOKEN);
	discord_set_on_ready(client, &on_ready);
	discord_set_on_interaction_create(client, &on_interaction);
	discord_run(client);
}

