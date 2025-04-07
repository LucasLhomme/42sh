/*
** EPITECH PROJECT, 2024
** sort params
** File description:
** sort params BOOTCAMP
*/
#include "lib.h"
int sort_params(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        my_putstr(argv[i]);
        my_putchar('\n');
    }
    return 0;
}
