#ifndef SHELL_H
#define SHELL_H

/*
Forks a child and runs the command specified in the array

Normally will return 0, but if the shell requests to terminate, will
return a non-zero number
*/
int execute(char**);

/*
functionality for parent process
*/
int parent_run(char**);

/*
functionality for child process
*/
int child_run(char**);

/*
if the command contains a pipe, pipe the output of first command
into input of second
*/
int pipe_run(char**, char**);

#endif
