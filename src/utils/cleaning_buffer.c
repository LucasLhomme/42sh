/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** cleaning_buffer
*/

#include "lib.h"

char *cleaning_buffer(char *str)
{
    char *end = str + my_strlen(str) - 1;

    for (; *str == ' ' || *str == '\t'; str++);
    for (; end > str && (*end == ' ' || *end == '\t'); end--)
        *end = '\0';
    return str;
}
