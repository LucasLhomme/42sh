/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** lol jsp
*/

#include <errno.h>
#include <stdio.h>
#include "../../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0') {
        if (s1[i] == s2[i]) {
            i++;
            continue;
        }
        if (s1[i] != s2[i]) {
            return 84;
        }
    }
    return 0;
}
