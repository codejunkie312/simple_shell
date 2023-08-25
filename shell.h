#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#define BUFFER_SIZE 1024
extern char **environ;

char *find_path(char *command);
void print_env(void);
char *_getline(FILE *stream);
char *_strtok(char *str, char *delim);
char *_strtok1(char *str, char *delim);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int _atoi(char *s);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
int _strlen(char *s);
char *_strchr(char *s, char c);
int _sprintf(char *str, const char *format, ...);
char *_strcpy(char *dest, char *src);
void setenv_case(char *argv[]);
void unsetenv_case(char *argv[]);
int command_loop(void);
int execute_command(char *command);
void parse_command(char *command, char *argv[]);
int handle_sepcial_commands(char *argv[]);
void handle_command(char *command);
void handle_logical_operators(char *command_iterator);
char *_strtok2(char *str, char *delim);
char *trim_spaces(char *str);
void cd_case(char *argv[]);
char *_getenv(char *name);
unsigned int _strspn(char *s, char *accept);
unsigned int _strcspn(char *s, char *accept);
int _fprintf(FILE *stream, const char *format, ...);
int _fputc(int c, FILE *stream);
int _fputs(char *s, FILE *stream);
char *_strdup(char *str);
int _fgetc(FILE *stream);
char *_strcat(char *dest, char *src);


#endif /* SHELL_H */
