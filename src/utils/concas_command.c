/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** concas_command
*/

#include "lib.h"
#include "my.h"

char *concas_command(char **argv, char **env)
{
    char *path = NULL;
    char *env_path = NULL;

    if (!argv[0])
        return NULL;
    for (int i = 0; env && env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            env_path = env[i] + 5;
            break;
        }
    }
    if (!env_path || env_path[0] == '\0')
        return NULL;
    path = malloc(my_strlen("/bin/") + my_strlen(argv[0]) + 1);
    if (path == NULL)
        return NULL;
    my_strcpy(path, "/bin/");
    my_strcat(path, argv[0]);
    cleaning_buffer(path);
    return path;
}
