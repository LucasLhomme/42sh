/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** nonalphanumeric
*/

int nonalphanum(char c)
{
    if ((c >= 'a' && c <= 'z') ||
    (c >= 'A' && c <= 'Z') ||
    (c >= '0' && c <= '9') ||
    (c == '.') || (c == '_')) {
        return 0;
    }
    return 1;
}
