/*
** EPITECH PROJECT, 2024
** my_compute_prime
** File description:
** nombre premier
*/

int my_is_prime(int nb)
{
    if (nb <= 1)
        return 0;
    for (int i = 2; i * i <= nb; i++) {
        if (nb % i == 0) {
            return 0;
        }
    }
    return 1;
}
