/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** faire la racine si c'est un carré parfait
*/

int my_compute_square_root(int nb)
{
    int result = 0;

    if (nb == 1)
        return 1;
    while (result != nb) {
        if (nb == result * result)
            return result;
        result = result + 1;
    }
    return 0;
}
