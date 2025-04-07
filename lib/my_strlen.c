/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** compte le nombre de lettre
*/

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
    i++;
    return (i);
}
