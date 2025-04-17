/*
** EPITECH PROJECT, 2024
** B-CPE-110-LIL-1-1-organized-joseph.birck
** File description:
** str_to_digit.c
*/

#include "../../include/my.h"

int str_to_digit(const char *str)
{
    int result = 0;
    int sign = 0;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9')
            result = result * 10 + (str[i] - '0');
        else
            return 0;
        i++;
    }
    return result;
}
