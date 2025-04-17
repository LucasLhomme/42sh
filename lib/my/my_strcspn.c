/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** my_strcspn
*/

#include <stdio.h>
#include <stddef.h>

int is_char_in_str(char c, const char *s2)
{
    for (size_t j = 0; s2[j] != '\0'; j++) {
        if (c == s2[j])
            return 1;
    }
    return 0;
}

size_t my_strcspn(const char *s1, const char *s2)
{
    size_t i;

    for (i = 0; s1[i] != '\0'; i++) {
        if (is_char_in_str(s1[i], s2))
            return i;
    }
    return i;
}
