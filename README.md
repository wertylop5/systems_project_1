# shell

By Stanley Lin and Sabrina Wen

## Features:
* Fork and execute commands
* Use strings in commands (grep!!!)
* Pipe commands together (limited to one point)


## Attempted features:


## Bugs:
* The \ in escaped quotes are not removed in the final string
* Cannot handling semicolons within a string
* If one command in a list of commands is invalid, then every command that follows will be invalid.

## Functions:
* `parse.c`
	* `char* read_line()`
		* Reads a line of input, splitting the line on ';'.
		* Returns:
			* `char*`: An array with each element being an unparsed command
	* `int semis(char*)`
		* Counts the number of args that are seperated by semicolons
		* Params:
			* `char*`: A command string
		* Returns:
			* `int`: The number of arguments
	* `char** parse_semis(char*)`
		* Uses output from read_line
	* `char** parse_args(char*)`
		* Splits the passed command string by spaces into its individual arguments
		* Params:
			* `char*`: A command string
		* Returns:
			* `char**`: An array containing each individual element of the command
	* `char* strip(char*)`
		* Strips extra whitespace from the front and back
		* Params:
			* `char*`: The string to be stripped
		* Returns:
			* `char*`: A new string with all leading and trailing whitespace removed
	* `int char_exists(char**, char*)`
		* Checks if a string with a single character exists in the command.
		* Params:
			* `char**`: An array of strings. Must be terminated with a NULL string
			* `char*`: A string with only one character
		* Returns:
			* `int`: The index of the specified character, or -1 if it is not found
	* `char* arr_strncat(char*, char**)`
		* Concats all the elements of a string array into a single string. The string array must be terminated with NULL as the last element. This function will stop when it reaches a NULL string.
		* Params:
			* `char*`: The destination where the resulting string will be stored
			* `char**`: The source array of strings
		* Returns:
			* `char*`: The destination string
	* `size_t command_size(char**)`
		* Counts the number of arguments in an array
		* Params:
			* `char**`: An array of strings. Must be terminated with a NULL string
		* Returns:
			* `size_t`: The size of the array
* `shell.c`
	* `int execute(char**)`
		* Forks a child and runs the command specified in the array. Normally will return 0, but if the shell requests to terminate, will return a non-zero number
		* Params:
			* `char**`: An array of strings containing command arguments
		* Returns:
			* `int`: Either 0 or a non-zero number
	* `int parent_run(char**)`
		* Functionality for parent process
		* Params:
			* `char**`: An array of strings containing command arguments
		* Returns:
			* `int`: Normally 0, non-zero if requesting to exit
	* `int child_run(char**)`
		* Functionality for child process
		* Params:
			* `char**`: An array of strings containing command arguments
		* Returns:
			* `int`: Normally 0
	* `int pipe_run(char**, char**)`
		* If the command contains a pipe, pipe the output of first command into input of second
		* Params:
			* `char**`: The first command to run
			* `char**`: The command to pipe into
		* Returns:
			* `int`: Normally 0 for success
