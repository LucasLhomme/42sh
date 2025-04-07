/*
** EPITECH PROJECT, 2024
** my swap
** File description:
** SWAP BOOTCAMP
*/
#include "lib.h"
void my_swap(int *a, int *b)
{
    int i = *a;

    *a = *b;
    *b = i;
    my_printf("a: %d, b: %d\n", *a, *b);
}
