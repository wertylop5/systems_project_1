#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include"../include/shell.h"

#define REQUEST_EXIT	2
#define REQUEST_CD	3

int execute(char **command) {
	int is_parent = fork();
	
	if (is_parent) {
		return parent_run(command);
	}
	else {
		return child_run(command);
	}
	
	return 0;
}

int parent_run(char **command) {
	int status;
	wait(&status);
	
	switch (WEXITSTATUS(status)) {
		
		//exit command was called
		case REQUEST_EXIT:
			return REQUEST_EXIT;
		break;
		
		//cd was called
		case REQUEST_CD:
			if (!command[1]) {
				//bash evals this as HOME
				chdir(getenv("HOME"));
			}
			else if (chdir(command[1]) == -1) {
				printf("%s: %s\n", command[1], strerror(errno));
			}
		break;
		
		//normal operation
		case 0:
		break;
		
		//abnormal operation
		default:
			printf("%s: command not found\n", command[0]);
		break;
	}
	
	//should usually be 0 if successful
	printf("child exited with: %d\n", WEXITSTATUS(status));
	
	return 0;
}

int child_run(char **command) {
	//special command handling
	if (strcmp(command[0], "exit") == 0) {
		exit(REQUEST_EXIT);
	}
	else if (strcmp(command[0], "cd") == 0) {
		exit(REQUEST_CD);
	}
	
	//run the specified command, return -1 if failure
	if (execvp(command[0], command) == -1) {
		printf("exec errno %d: %s\n", errno, strerror(errno));
		exit(-1);
	}
	return 0;	//should never run?
}

