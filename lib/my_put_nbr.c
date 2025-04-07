/*
** EPITECH PROJECT, 2024
** my put nbr
** File description:
** affiche un chiffre
*/

#include "lib.h"

int my_put_nbr(int nb)
{
    int beginning = nb / 10;
    int end = nb % 10;

    if (nb < 0) {
        my_putchar('-');
        if (nb < - 2147483647 + 1) {
            my_put_nbr(- beginning);
            return my_put_nbr(- end);
        }
        return my_put_nbr(- nb);
    }
    if (beginning != 0) {
        my_put_nbr(beginning);
        my_putchar(end + '0');
    } else {
        my_putchar(end + '0');
    }
    return 0;
}
