#ifndef PARSE_H
#define PARSE_H

//reads a line of input, splitting the line on ';'
char* read_line();

//uses output from read_line
char** parse_args(char*);

/*
Strips extra whitespace from the front and back

param: the string to split, will be modified
returns: a new string with surrounding whitespace removed
*/
char* strip(char*);

#endif
