#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 1024
extern char **environ;
static char buffer[BUFFER_SIZE];
static int buffer_pos = 0;
static int line_len = 0;

char *find_path(char *command);
void print_env(void);
char *_getline(FILE *stream);

#endif /* SHELL_H */
