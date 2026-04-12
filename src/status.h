#pragma once

#include <inttypes.h>

#define CLOCKIN_STATUSES(F) \
	F(CLOCKIN_SUCCESS, "success") \
	F(CLOCKIN_FAIL, "generic failure") \
	F(CLOCKIN_TASK_FILE_READ_FAIL, "failed to read the task file!") \
	F(CLOCKIN_INSUFFICIENT_TASK_MEMORY, "insufficient memory allocated for task storage!") \
	F(CLOCKIN_TASK_BUFFER_CAPACITY_TOO_SMALL, "task buffer capacity too small!")\


#define CHOOSE_ENUM(E, S) E,
#define CHOOSE_STR(E, S) S,

typedef enum { CLOCKIN_STATUSES(CHOOSE_ENUM) } clockin_status_t;

static const char* clockin_status_strings[] = { CLOCKIN_STATUSES(CHOOSE_STR) };

