/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** searching_bin
*/
#include "lib.h"
#include "my.h"

int searching_bin(char *buffer, char **env)
{
    char **argv = NULL;
    char *path = NULL;

    argv = my_str_to_word_array(buffer);
    if (argv == NULL || argv[0] == NULL) {
        my_printf("%s: Command not found.\n", buffer);
        return 1;
    }
    path = concas_command(argv);
    if (access(path, X_OK) == 0)
        return execute_bin(path, argv, env);
    else {
        my_printf("%s: Command not found.\n", argv[0]);
        free(path);
        for (int i = 0; argv[i] != NULL; i++)
            free(argv[i]);
        free(argv);
        return 1;
    }
}
