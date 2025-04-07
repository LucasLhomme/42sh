/*
** EPITECH PROJECT, 2025
** B-CPE-110-LIL-1-1-secured-lucas.lhomme
** File description:
** isalphanum
*/

int isalphanum(char c)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
            c == '-' || c == '/' || c == '.' ||
            c == '_' || c == '=' || c == ':' || c == '%')
        return 1;
    return 0;
}
