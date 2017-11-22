#ifndef SHELL_H
#define SHELL_H

char* read_line();

//uses output from read_line
char** parse_args(char*);

//handles forking and exec child
void run_command(char **);

#endif
