/*
** EPITECH PROJECT, 2024
** my_print_comb
** File description:
** my_print_comb BOOTCAMP
*/
#include "lib.h"

int my_print_comb(void)
{
    for (int nbr1 = '0'; nbr1 <= '9'; nbr1++) {
        for (int nbr2 = '0'; nbr2 < nbr1; nbr2++) {
            my_putchar(nbr2);
        }
        my_putchar(nbr1);
        if (nbr1 != '9') {
            my_putchar(',');
            my_putchar(' ');
        }
    }
    my_putchar('\n');
    return 0;
}
