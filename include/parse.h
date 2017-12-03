#ifndef PARSE_H
#define PARSE_H

#include<stdlib.h>

/*
reads a line of input, splitting the line on ';'
returns a char* array with each element being an unparsed command
*/
char* read_line();

//uses output from read_line
int semis(char*);
char** parse_semis(char*);
char** parse_args(char*);

/*
Strips extra whitespace from the front and back

param: the string to split, will be modified
returns: a new string with surrounding whitespace removed
*/
char* strip(char*);

/*
Checks if a string with a single character exists in the command.

If so, will return the index at which it is located.
Else, will return -1
*/
int char_exists(char**, char*);

/*
Concats all the elements of a string array into a single
string. The string array must be terminated with NULL as
the last element. This function will stop when it reaches
a NULL string.

first arg is the destination
second arg is the source array

returns the destination
*/
char* arr_strncat(char*, char**);

/*
Returns number of elements in command array
*/
size_t command_size(char**);

#endif
