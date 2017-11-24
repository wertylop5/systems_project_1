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


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/shell.h"

/*
char whitespace[] = {
	'\n',
	' ',
	'\t'
};
*/

char * read_line() { // read args + split semicolons
  char s[256];
  fgets(s, 256, stdin);
  printf("inputted string: %s\n", s);
  return 0;
}

char** parse_args(char *line) {
	char **arg_array = malloc(64*sizeof(char*));
	
	if (!strchr(line, ' ')) {
		*(arg_array) = line;
		*(arg_array+1) = 0;
		return arg_array;
	}
	
	int index = 0;
	char *temp;
	
	//get the args
	while(line) {
		temp = strsep(&line, " ");
		
		//in case there are extra spaces
		if (strlen(temp) > 1) {
			*(arg_array + (index++) ) = temp;
		}
	}
	
	*(arg_array + (index) ) = 0;
	
	return arg_array;
}

char* strip(char *line) {
	char *result = (char*)malloc(sizeof(line));
	
	//strip the front
	while ( *line && isspace( *line ) ) line++;
	
	//strip the back
	char *back = strchr(line, '\n');
	while ( back != line && isspace( *back ) ) back--;
	if (back == line) return 0;
	*(back+1) = 0;
	
	//create the new string
	result = line;
	int index = 0;
	while (*line) *(result + (index++)) = *(line++);
	
	return result;
}

