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

#include "../include/parse.h"

/*
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
		if (strlen(temp) > 0 && !isspace(*temp)) {
			*(arg_array + (index++) ) = temp;
		}
	}

	*(arg_array + (index) ) = 0;

	return arg_array;
}
*/

char * read_line() { // read args
  char * s;
	//printf("lol\n");
  s = (char *)calloc(256,sizeof(char)); // idk why malloc does not work :(
	printf("Command? "); // printf should go before fgets or else risk infinite loop
	fgets(s, 256, stdin);
  s[strlen(s) - 1] = 0; // remove new line
  //printf("length of input: %d", strlen(s));
	return s;
}

// does not actually remove semicolons yet
char * parse_semis(char * line) { // remove semicolons
  int num_args = 0;
  while (*line) { // counts up num of semis in fgets in order to get num of args
    if (strchr(line, ';')) {
      //args[num_args] = strsep(&line, ";");
      num_args++;
      line = strchr(line+1,';'); // moving on to char right after first occurrence of a semi in the string
    }
    line++;
  }
  num_args++;
  int count = 0;
  char ** args = (char **)calloc(num_args, sizeof(char[256]));
  while (line) {
    char * temp = strsep(&line, ";");
    printf("adding this val to args array: %s\n", temp);
    args[count] = temp;
    count++;
  }
  //printf("first arg: %s\n", args[0]);
  return line;
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
		/*
		see if quotes exist in the string
		treat single quote as double quote (single acts strangely?)

		if first char of rest of string is quote
			set some variable
			search for second quote

			if \ before quote
				ignore and search again
			else
				set pointer from first quote to second quote as string

			if none found
				throw error
		else
			operate as before
		*/

		//BUG: \ are not removed
		if (*line == '\'' || *line == '\"') {
			printf("found first quote: %c\n", *line);
			char *quote_temp;
			temp = line++;

			while (1) {
				//if no more matching quotes exist
				if ( !(quote_temp = strchr(line, *temp)) ) {
					printf("error parsing string\n");
					return 0;
				}

				//is the quote escaped?
				if ( *(quote_temp - 1) != '\\' ) {
					printf("found second quote: %c\n", *quote_temp);
					printf("str len is: %ld\n", quote_temp - temp - 1);

					printf("temp+1: %c, temp: %c, quote_temp: %c\n", *(temp+1), *temp, *quote_temp);

					//advance the string past the last quote so it doesn't search again
					line = quote_temp + 1;

					//don't want to copy any of the quotes themselves into the string
					size_t n = quote_temp - temp - 1;

					quote_temp = malloc(quote_temp - temp);
					strncpy(quote_temp, temp+1, n);

					printf("full str: %s\n", quote_temp);
					*(arg_array + (index++) ) = quote_temp;

					break;
				}
				else {
					line = quote_temp + 1;
				}
			}
		}
		else {
			temp = strsep(&line, " ");

			//in case there are extra spaces
			if (strlen(temp) > 0 && !isspace(*temp)) {
				*(arg_array + (index++) ) = temp;
			}
		}
	}

	*(arg_array + (index) ) = 0;

	return arg_array;
}

char* strip(char *line) {
	char *result = (char*)malloc(sizeof(line));

	//strip the front
	while ( *line && isspace( *line ) ) line++;
	//if (!*line) return 0;

	//strip the back
	char *back = strchr(line, '\n');
	while ( back > line && isspace( *back ) ) back--;
	if (back < line) return 0;
	*(back+1) = 0;

	//create the new string
	result = line;
	int index = 0;
	while (*line) *(result + (index++)) = *(line++);

	return result;
}

int pipe_exists(char **command) {
	int index = 0;
	for (; *(command+index); index++) {
		if ( !strcmp(*(command+index), "|") ) return index;
	}

	return -1;
}

char* arr_strncat(char *dest, char **src) {
	while (*src) {
		strncat(dest, *src, strlen(*src));
		strncat(dest, " ", 1);
		src++;
	}

	return dest;
}
