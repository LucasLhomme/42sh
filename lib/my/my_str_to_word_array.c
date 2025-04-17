/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Function de la mort qui tue
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/struct_word_array.h"

int is_alnum(char c)
{
    return (c == ' ' || c == '\t');
}

char **allocate_word_array(const char *str)
{
    int word_count = count_words(str);
    char **tab = malloc(sizeof(char *) * (word_count + 1));

    if (tab == NULL) {
        return NULL;
    }
    return tab;
}

void add_word_to_array(char const *str,
    word_array_t *word_array, int start, int i)
{
    word_array->tab[word_array->index] = copy_word(str, start, i);
    word_array->index++;
}

char **my_str_to_word_array(char const *str)
{
    char **tab = allocate_word_array(str);
    word_array_t word_array = {tab, 0};

    if (tab == NULL) {
        return NULL;
    }
    fill_word_array(str, &word_array);
    return tab;
}
