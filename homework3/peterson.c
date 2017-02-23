#define _PETERSON_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peterson.h"

int init_peterson(int max_pid) {
	size_t mem_size = sizeof(int *) * (max_pid + 1);
	level = malloc(mem_size);
	last_enter = malloc(mem_size);
	if (level == NULL || last_enter == NULL) {
		return FALSE;
	}
	else {
		memset(level, ZERO_STATE, mem_size);
		last_enter[0] = level[0] = max_pid;
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
		while(last_enter[i] == pid && is_highest_level(pid) == FALSE)
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
	level[pid] = ZERO_STATE;
}
