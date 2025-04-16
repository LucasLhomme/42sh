/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** execute command
*/

#include "my.h"
#include "lib.h"

int execute_bin(char *path, char **argv, char **env)
{
    int status = 0;

    if (fork() == 0)
        status = execve(path, argv, env);
    wait(&status);
    free(path);
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
    return WEXITSTATUS(status);
}
