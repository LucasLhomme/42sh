/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** my_atoi
*/

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
        str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
        i++;
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}
