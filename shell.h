#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 1024
extern char **environ;

char *find_path(char *command);
void print_env(void);
char *_getline(FILE *stream);
char *_strtok(char *str, const char *delim);
char *_strtok1(char *str, const char *delim);

#endif /* SHELL_H */
