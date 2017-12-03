#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>

#include"../include/shell.h"
#include"../include/parse.h"

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
			printf("An error occured with your command. Please try again\n");
		break;
	}
	
	//should usually be 0 if successful
	//printf("child exited with: %d\n", WEXITSTATUS(status));
	
	return 0;
}

int child_run(char **command) {
	int char_index;
	if ( (char_index = char_exists(command, "|")) != -1 ) {
		//create a new array that ends before the found char
		char *temp[512];
		memcpy(temp, command, char_index*sizeof(char*) );
		
		pipe_run(temp, command+char_index+1);
		exit(0);
	}
	if ( (char_index = char_exists(command, ">")) != -1 ) {
		int targ_out = open(*(command+char_index+1), O_CREAT | O_WRONLY, 0644);
		dup2(targ_out, 1);
		
		//remove the >, along with the target file from the command array
		memmove(command+char_index,
			command+char_index+2,
			(command_size(command) - char_index + 1) * sizeof(char*));
	}
	if ( (char_index = char_exists(command, "<")) != -1 ) {
		int targ_in = open(*(command+char_index+1), O_RDONLY);
		if (targ_in == -1) {
			printf("%s: %s\n", *(command+char_index+1), strerror(errno));
			exit(1);
		}
		dup2(targ_in, 0);
		
		memmove(command+char_index,
			command+char_index+2,
			(command_size(command) - char_index + 1) * sizeof(char*));
	}
	
	//interestingly enough, you can actually pipe exit and cd
	//hence why they weren't parsed before the pipe
	
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

int pipe_run(char **cmd1, char **cmd2) {
	printf("piping\n");
	
	char cmd1_str[512];
	char cmd2_str[512];
	
	cmd1_str[0] = cmd2_str[0] = 0;
	
	arr_strncat(cmd1_str, cmd1);
	arr_strncat(cmd2_str, cmd2);
	
	FILE *one = popen(cmd1_str, "r");
	FILE *two = popen(cmd2_str, "w");
	
	char input[512];
	
	//reads one line of input at a time
	while (fgets(input, sizeof(input), one)) {
		int len = fprintf(two, "%s", input);
		//printf("%d bytes written\n", len);
	}
	
	pclose(one);
	pclose(two);
	
	return 0;
}

