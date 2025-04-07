/*
** EPITECH PROJECT, 2024
** Raciné carré
** File description:
** carré comme le projet
*/

int my_compute_square_root(int nb)
{
    int i = 0;

    if (nb <= 0)
        return (0);
    for (; i * i != nb; i++) {
        if (i > nb)
            return (0);
    }
    return (i);
}
