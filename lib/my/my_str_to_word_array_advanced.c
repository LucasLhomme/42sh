/*
** EPITECH PROJECT, 2025
** lib
** File description:
** My_str_to_word_array_advanced
*/

#include <stdlib.h>
#include <stdio.h>

static int my_isalphanum_advanced(const char c, char *extra_chars)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
        return 1;
    for (int i = 0; extra_chars[i] != '\0'; i++) {
        if (c == extra_chars[i])
            return 1;
    }
    return 0;
}

static int my_isnonalphanum_advanced(const char c, char *extra_chars)
{
    return !my_isalphanum_advanced(c, extra_chars);
}

char *allocate_word_advanced(char *str, int start, int end)
{
    int length = end - start;
    char *word = malloc((length + 1) * sizeof(char));

    if (word == NULL)
        return NULL;
    for (int i = 0; i < length; i++)
        word[i] = str[start + i];
    word[length] = '\0';
    return word;
}

int count_word_advanced(char *str)
{
    int word = 0;
    int word_in = 0;
    int is_alnum = 0;

    if (str == NULL)
        return 84;
    for (int i = 0; str[i]; i++) {
        is_alnum = ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9'));
        if (is_alnum && !word_in) {
            word++;
            word_in = 1;
        }
        if (!is_alnum)
            word_in = 0;
    }
    return word;
}

int while_kskip_advanced(char *str, int k, char *extra_chars)
{
    while (my_isalphanum_advanced(str[k], extra_chars))
        k++;
    return k;
}

char *word_in_array_advanced(char *str, int k, char *extra_chars)
{
    int start = k;
    int end = 0;
    char *new_str = NULL;

    k = while_kskip_advanced(str, k, extra_chars);
    end = k;
    new_str = allocate_word_advanced(str, start, end);
    if (new_str == NULL)
        return NULL;
    k--;
    return new_str;
}

char **my_str_to_word_array_advanced(char *str, char *extra_chars)
{
    int words = count_word_advanced(str);
    char **tab = NULL;
    int i = 0;

    if (str == NULL)
        return NULL;
    tab = malloc((words + 1) * sizeof(char *));
    if (tab == NULL)
        return NULL;
    for (int k = 0; str[k] != '\0'; k++) {
        if (my_isalphanum_advanced(str[k], extra_chars) && (k == 0 ||
            my_isnonalphanum_advanced(str[k - 1], extra_chars))) {
            tab[i] = word_in_array_advanced(str, k, extra_chars);
            i++;
        }
    }
    tab[i] = NULL;
    return tab;
}
