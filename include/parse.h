#ifndef PARSE_H
#define PARSE_H

/*
reads a line of input, splitting the line on ';'
returns a char* array with each element being an unparsed command
*/
char* read_line();

//uses output from read_line
char** parse_args(char*);

/*
Strips extra whitespace from the front and back

param: the string to split, will be modified
returns: a new string with surrounding whitespace removed
*/
char* strip(char*);

/*
Checks if the pipe character ('|') exists in the command.

If so, will return the index at which it is located.
Else, will return -1
*/
int pipe_exists(char**);

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

#endif
