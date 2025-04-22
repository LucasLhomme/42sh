/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** utils
*/

#include <unistd.h>

void write_char(int *pos, int *len)
{
    for (int i = 0; i < *len - *pos; i++)
        write(1, "\b", 1);
}
