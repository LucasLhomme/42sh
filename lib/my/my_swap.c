/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** swapp two int
*/

void my_swap(int *a, int *b)
{
    int nb_swap = 0;

    nb_swap = *b;
    *b = *a;
    *a = nb_swap;
}
