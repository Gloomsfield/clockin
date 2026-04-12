CFLAGS = -Wall -std=c99 -g
LFLAGS = -lcurl -ldiscord

SRC_DIR = src
BUILD_DIR = build
SECRETS_DIR = secrets

SRC_FILES = main.c parser.c state.c task-buffer.c task.c

SRC_PATHS = $(SRC_FILES:%=$(SRC_DIR)/%)

OBJ_PATHS = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/clockin: $(OBJ_PATHS)
	clang $(OBJ_PATHS) $(LFLAGS) -o $@

-include $(OBJ_PATHS:%.o=%.d)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	@clang -DBOT_TOKEN=\"$$(cat $(SECRETS_DIR)/bot_token.txt)\" -DGUILD_ID=$$(cat $(SECRETS_DIR)/guild_id.txt) -MMD -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

