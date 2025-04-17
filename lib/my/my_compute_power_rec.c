/*
** EPITECH PROJECT, 2024
** mmy_compute_power_rec
** File description:
** au carré rrecurrence
*/

int my_compute_power_rec(int nb, int p)
{
    if (nb >= 12 || p >= 12)
        return 0;
    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    nb = nb * my_compute_power_rec(nb, p - 1);
    return nb;
}
