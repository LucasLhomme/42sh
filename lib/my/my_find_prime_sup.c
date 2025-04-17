/*
** EPITECH PROJECT, 2024
** my_find_prime_sup
** File description:
** trouver un nombre premiers sup
*/

#include "../../include/my.h"

int my_find_prime_sup(int nb)
{
    int value;

    if (!nb)
        return -1;
    value = nb;
    while (!my_is_prime(value)) {
        value++;
    }
    nb = value;
    return 0;
}
