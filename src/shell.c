#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include"../include/shell.h"

void execute(char **command) {
	int is_parent = fork();
	int status;
	
	if (is_parent) {
		wait(&status);
		if (WEXITSTATUS(status) != 0) {
			printf("errno %d: %s\n", errno, strerror(errno));
		}
		printf("child exited with: %d\n", WEXITSTATUS(status));
	}
	else {
		exit(execvp(command[0], command));
	}
}
