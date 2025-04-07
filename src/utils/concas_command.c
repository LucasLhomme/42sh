/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** concas_command
*/
#include <stddef.h>
#include "lib.h"
#include "my.h"

char *concas_command(char **argv)
{
    char *path = NULL;

    path = malloc(my_strlen("/bin/") + my_strlen(argv[0]) + 1);
    if (!argv[0] || path == NULL)
        return NULL;
    my_strcpy(path, "/bin/");
    my_strcat(path, argv[0]);
    cleaning_buffer(path);
    return path;
}
