#ifndef SHELL_H
#define SHELL_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* Constants */
#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"
#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_LENGTH 1024
#define MAX_ALIAS_NAME_LENGTH 128
#define MAX_ALIAS_VALUE_LEGTH 256

/* Function Prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void display_prompt();
char *custom_getline();
char **split_arguments(char *line);
char *expand_variables(char *line);
int execute_command(char **args);
void execute_commands(char *line);
void handle_signal(int sig);

/* Built-in Commands */
int shell_cd(char **args);
int shell_exit(char **args);
int shell_env(char **args);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_alias(char **args);

#endif /* SHELL_H */
