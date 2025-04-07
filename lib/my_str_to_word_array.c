/*
** EPITECH PROJECT, 2024
** my_str_to_word_arry
** File description:
** my_str_to_word_arry BOOTCAMP
*/
#include "lib.h"

int isnonalphanum(char c)
{
    return !isalphanum(c);
}

int count_word(char const *str)
{
    int count = 0;

    if (str == NULL)
        return 84;
    for (int i = 0; str[i]; i++) {
        if (isalphanum(str[i]) && (i == 0 || isnonalphanum(str[i - 1]))) {
            count++;
        }
    }
    return count;
}

char **my_str_to_word_array(const char *str)
{
    int i = 0;
    int start = -1;
    int end;
    char **tab = malloc(sizeof(char *) * (count_word(str) + 1));

    if (tab == NULL || str == NULL)
        return NULL;
    for (int k = 0; str[k] != '\0'; k++) {
        if (isalphanum(str[k]) && (k == 0 || isnonalphanum(str[k - 1])))
            start = k;
        if (start != -1 && (str[k + 1] == '\0' || isnonalphanum(str[k + 1]))) {
            end = k + 1;
            tab[i] = my_strndup(str + start, end - start);
            i++;
            start = -1;
        }
    }
    tab[i] = NULL;
    return tab;
}
