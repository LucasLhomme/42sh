/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** my_isalpha
*/

int my_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '.') || (c == '_'))
        return 1;
    return 0;
}
