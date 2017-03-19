#include <stdlib.h>
#include "peterson.h"

int main(int argc, char *argv[]) {
	/* parse argv[1] as the largest process id */
	if (argc < 2 || !init_peterson(argv[1])) {
		exit(EXIT_FAILURE);
	}

	/* generate mutil processes or threads */

	int process = 1; // assign its own process id
	enter_region(process);

	/* do critical section */

	leave_region(process);

	/* only call close_peterson() in parent process or main thread */
	if (process == 1) {
		close_peterson();
	}

	exit(EXIT_SUCCESS);
}
