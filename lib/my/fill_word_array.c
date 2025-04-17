/*
** EPITECH PROJECT, 2024
** fill_word_array
** File description:
** fill word array (my str to word array)
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/struct_word_array.h"

void process(const char *str, word_array_t *word_array,
    int start, int end)
{
    if (end > start) {
        word_array->tab[word_array->index] = copy_word(str, start, end);
        word_array->index++;
    }
}

void fill_word_array(char const *str, word_array_t *word_array)
{
    int start = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && start == -1) {
            start = i;
            continue;
        }
        if (str[i] == ' ' && start != -1) {
            process(str, word_array, start, i);
            start = -1;
        }
    }
    if (start != -1) {
        process(str, word_array, start, my_strlen(str));
    }
    word_array->tab[word_array->index] = NULL;
}
