/*
** EPITECH PROJECT, 2024
** my compute power rec
** File description:
** fonction recursive
*/
#include <limits.h>

int my_compute_power_rec(int nb, int p)
{
    if (p == 0) {
        return 0;
    }
    if (p < 0) {
        return 0;
    }
        return (nb * my_compute_power_rec(nb, p - 1));
}
