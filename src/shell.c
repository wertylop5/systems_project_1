/*
read line
parse arguments
fork off a child process
	child: exec with args
	parent: wait until child finish

if cd:
	use chdir

if command == exit
	exit(0)
*/
#include<string.h>

#include"include/shell.h"

char* read_line() {
	return 0;
}

/*
Will split command string on spaces
*/
char** parse_args(char *line) {
	char **result;
	
	line = strsep(result, ";")
	
	return 0;
}

