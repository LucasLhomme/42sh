/*
** EPITECH PROJECT, 2024
** my_strstr
** File description:
** str un str dans un str
*/
#include <stddef.h>

char *my_strstr(char *str, char *to_find)
{
    char *a = NULL;
    char const *b = NULL;

    if (str == NULL)
        return NULL;
    if (*to_find == '\0')
        return str;
    while (*str != '\0') {
        a = str;
        b = to_find;
        while (*a == *b && *b != '\0') {
            a++;
            b++;
        }
        if (*b == '\0')
            return str;
        str++;
    }
    return NULL;
}
