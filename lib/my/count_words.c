/*
** EPITECH PROJECT, 2024
** count_words
** File description:
** compteur de mots str to word array
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/struct_word_array.h"

int count_words(const char *str)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_alnum(str[i]) && !in_word) {
            in_word = 1;
            count++;
        }
        if (!is_alnum(str[i])) {
            in_word = 0;
        }
    }
    return count;
}
