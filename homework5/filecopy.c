#include <sys/types.h>
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]); 

#define BUF_SIZE 4096		/* use a buffer size of 4096 bytes */
#define OUTPUT_MODE 0700	/* protection bits for output file */
#define TRUE 1
/* error message auxiliary */
#define ERRMSG(errf) fprintf(stderr, errf " Error: %s\n", strerror(errno))

int main(int argc, char *argv[]) {
	int in_fd, out_fd, rd_count, wt_count, err; 
	char buffer[BUF_SIZE];

	if (argc != 3) {
		printf("Invalid number of arguments");
		printf("Usage: filecopy [existing file] [target file]");
		exit(1);
	}

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0) {
		ERRMSG("open()");
		exit(2);
	}

	out_fd = creat(argv[2], OUTPUT_MODE);
	if (out_fd < 0) {
		ERRMSG("creat()");
		exit(3);
	}

	while (TRUE) {
		rd_count = read(in_fd, buffer, BUF_SIZE);
		if (rd_count <= 0) {
			if (rd_count < 0) {
				ERRMSG("read()");
			}
			break;
		}
		wt_count = write(out_fd, buffer, rd_count);
		if (wt_count <= 0) {
			ERRMSG("write()");
			exit(4);
		}
	}

	close(in_fd); 
	close(out_fd);

	if (rd_count == 0)
		exit(0);
	else {
		exit(5);
	}
}
