#define _PETERSON_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "peterson.h"

int init_peterson(char *s_max_pid) {
	int max_pid = strtol(s_max_pid, NULL, 0);
	if (max_pid == 0) {
		int err = errno;
		printf("invalid maximum pid\n");
		if (errno == ERANGE) {
			printf("strtol error: %s\n", strerror(err));
		}
		return FALSE;
	}
	else {
		size_t mem_size = sizeof(int *) * (max_pid + 1);
		level = malloc(mem_size);
		last_enter = malloc(mem_size);
		if (level == NULL || last_enter == NULL) {
			printf("malloc error\n");
			return FALSE;
		}
		else {
			memset(level, LEVEL_ZERO, mem_size);
			last_enter[0] = level[0] = max_pid;
		}
	}
	return TRUE;
}

int close_peterson() {
	free(level);
	free(last_enter);
	return TRUE;
}

void enter_region(int pid) {
	int i;
	for (i = 1; i < last_enter[0]; i++) {
		level[pid] = i;
		last_enter[i] = pid;
		while(last_enter[i] == pid && !is_highest_level(pid))
			;
	}
}

int is_highest_level(int pid) {
	int i;
	for (i = 1; i <= level[0]; i++) {
		if (i != pid && level[i] >= level[pid]) {
			return FALSE;
		}
	}
	return TRUE;
}

void leave_region(int pid) {
	level[pid] = LEVEL_ZERO;
}
