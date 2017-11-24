#ifndef SHELL_H
#define SHELL_H

//reads a line of input, splitting the line on ';'
char* read_line();

//uses output from read_line
char** parse_args(char*);

//handles forking and exec child
void run_command(char **);

//strips extra whitespace from the front and back
char* strip(char*);

#endif
