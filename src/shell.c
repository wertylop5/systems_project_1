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
#include "include/shell.h"
#include "<unistd.h>"
#include "<stdio.h>"
#include "<stlib.h>"

char ls * read_line() { // read args + split semicolons
  char s[256];
  fgets(s, 256, stdin);
  printf("inputted string: %s\n", s);
  return 0;
}

char** parse_args(char *line) {
	return 0;
}

int main() {
  read_line();
  return 0;
}

