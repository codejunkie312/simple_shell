# Simple_Shell
## Functions used:
### find_path
This is a function that iterates through a command variable to find it within the `PATH` environement variable
usage:char find_path(char *command)
### print_env
This is a function that prints the available environment variables found in a shell terminal onto the screen
usage:void print_env(void)
### _getline
This function reads a line from the file stream and in this case that is the command line
usage: char *_getline(FILE *stream)
