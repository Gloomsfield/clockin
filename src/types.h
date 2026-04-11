#pragma once

#include <inttypes.h>

#define CLOCKIN_STATUSES(F) \
	F(CLOCKIN_SUCCESS, "success") \
	F(CLOCKIN_FAIL, "generic failure") \
	F(CLOCKIN_TASK_FILE_READ_FAIL, "failed to read the task file!") \
	F(CLOCKIN_INSUFFICIENT_TASK_MEMORY, "insufficient memory allocated for task storage!") \

#define CHOOSE_ENUM(E, S) E,
#define CHOOSE_STR(E, S) S,

typedef enum { CLOCKIN_STATUSES(CHOOSE_ENUM) } clockin_status_t;

static const char* clockin_status_strings[] = { CLOCKIN_STATUSES(CHOOSE_STR) };

typedef struct task_t {
	char description[512];
	char tags[256][64];
	uint32_t tag_count;
	uint32_t id;
} task_t;

typedef struct task_buffer_t {
	task_t* tasks;
	uint32_t capacity;
	uint32_t count;
} task_buffer_t;

