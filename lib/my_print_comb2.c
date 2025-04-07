/*
** EPITECH PROJECT, 2024
** My_print_comb2
** File description:
** my_print_comb2 BOOTCAMP
*/
#include "lib.h"

void print_comb(int nb1, int nb2)
{
    my_putchar('0' + nb1 / 10);
    my_putchar('0' + nb1 % 10);
    my_putchar(' ');
    my_putchar('0' + nb2 / 10);
    my_putchar('0' + nb2 % 10);
    if (nb1 != 98 || nb2 != 99){
        my_putchar(',');
        my_putchar(' ');
    }
}

int my_print_comb2(void)
{
    for (int nb1 = 0; nb1 <= 99; nb1++){
        for (int nb2 = nb1 + 1; nb2 <= 99; nb2++)
        print_comb(nb1, nb2);
    }
    return 0;
}
