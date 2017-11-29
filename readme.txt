shell

By Stanley Lin and Sabrina Wen

Features:
	Fork and execute commands
	Use strings in commands (grep!!!)
	Pipe commands together (limited to one point)
	

Attempted features:
	

Bugs:
	The \ in escaped quotes are not removed in the final string

Functions:
~~~~~~~~~~~~~~~~parse.c~~~~~~~~~~~~~~~~
	/*
	reads a line of input, splitting the line on ';'
	returns a char* array with each element being an unparsed command
	*/
	char* read_line();

	//uses output from read_line
	char* parse_semis(char*);
	
	char** parse_args(char*);
		Splits the passed command string by spaces into its individual arguments
		
		Params:
			char*: A command string
		
		Returns:
			char**: An array containing each individual element of the command

	char* strip(char*)
		Strips extra whitespace from the front and back
		
		Params:
			char*: The string to be stripped
		
		Returns:
			char*: A new string with all leading and trailing whitespace removed

	int pipe_exists(char**)
		Checks if the pipe character ('|') exists in the command.
		
		Params:
			char**: An array of strings. Must be terminated with a NULL string
		
		Returns:
			int: The index of the | character, or -1 if it is not found

	char* arr_strncat(char*, char**);
		Concats all the elements of a string array into a single
		string. The string array must be terminated with NULL as
		the last element. This function will stop when it reaches
		a NULL string.
		
		Params:
			char*: The destination where the resulting string will be stored
			char**: The source array of strings
		
		Returns:
			char*: The destination string


~~~~~~~~~~~~~~~~name.c~~~~~~~~~~~~~~~~
	int execute(char**);
		Forks a child and runs the command specified in the array
		
		Normally will return 0, but if the shell requests to terminate, will
		return a non-zero number
		
		Params:
			char**: An array of strings containing command arguments
		
		Returns:
			int: Either 0 or a non-zero number

	int parent_run(char**);
		Functionality for parent process
		
		Params:
			char**: 
		
		Returns: 
			int: Normally 0
	
	int child_run(char**);
		Functionality for child process
		
		Params:
			char**:
		
		Returns:
			int: Normally 0
	
	int pipe_run(char**, char**);
		if the command contains a pipe, pipe the output of first command
		into input of second
		
		Params:
			char**:
			char**:
		
		Returns:
			int: 

