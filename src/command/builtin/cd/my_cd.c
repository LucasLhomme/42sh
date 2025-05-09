/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_cd.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "project.h"
#include "my.h"

int is_file(char *path)
{
    struct stat stats;

    if (!path || stat(path, &stats) != 0)
        return -1;
    return S_ISREG(stats.st_mode);
}

static char *get_new_directory(char **args, env_t *head, char *oldpwd)
{
    if (!args[1] || my_strcmp(args[1], "~") == 0)
        return get_env("HOME", head);
    if (my_strcmp(args[1], "-") == 0) {
        if (!oldpwd || oldpwd[0] == '\0') {
            print_error("cd", "OLDPWD not set");
            return NULL;
        }
        return oldpwd;
    }
    return args[1];
}

void update_history(char history[2][1024])
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd))) {
        strncpy(history[0], history[1], 1024);
        strncpy(history[1], cwd, 1024);
    }
}

int handle_cd_errors(char *new_dir, int file_check)
{
    if (file_check == -1) {
        print_error(new_dir, "No such file or directory.");
        return 1;
    }
    if (file_check == 1) {
        print_error(new_dir, "Not a directory.");
        return 1;
    }
    if (chdir(new_dir) == -1) {
        print_error(new_dir, "Permission denied or invalid path.");
        return 1;
    }
    return 0;
}

static void use_useless_variables(char **env, int *exit_status)
{
    (void)env;
    (void)exit_status;
}

int my_cd(char **args, env_t *head, char **env, int *exit_status)
{
    static char history[2][1024] = {{0}};
    char cwd[1024];
    char *new_dir = NULL;
    int file_check = 0;

    use_useless_variables(env, exit_status);
    if (history[1][0] == '\0' && getcwd(cwd, sizeof(cwd)))
        strncpy(history[1], cwd, 1024);
    if (len_tab(args) > 1) {
        my_putstrerror("cd: Too many arguments.\n");
        return 1;
    }
    new_dir = get_new_directory(args, head, history[0]);
    if (!new_dir)
        return 1;
    file_check = is_file(new_dir);
    if (handle_cd_errors(new_dir, file_check))
        return 1;
    update_history(history);
    return 0;
}
