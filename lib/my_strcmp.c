/*
** EPITECH PROJECT, 2024
** jsp
** File description:
** jsp
*/
#include <stddef.h>
#include <stdio.h>

int my_strcmp(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i])
        return 1;
    }
    return 0;
}
