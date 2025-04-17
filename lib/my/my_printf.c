/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** faire le printf
*/
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "../../include/my.h"
#include "../../include/structid.h"

const format_t formats[] = {
    {'c', handle_char},
    {'s', handle_str},
    {'d', handle_int},
    {'i', handle_int},
    {'%', percent},
    {'x', handle_hex},
    {'X', handle_hexmaj},
    {'o', handle_oct},
    {'p', handle_ptr},
    {'f', flottant},
    {'e', handle_e},
    {'u', handle_unsigned},
    { '\0', NULL }
};

int parcour_flag(char flag, va_list ap)
{
    for (int i = 0; formats[i].symbol != '\0'; i++) {
        if (formats[i].symbol == flag) {
            return formats[i].handler(ap);
        }
    }
    return 0;
}

int my_printf(char const *format, ...)
{
    va_list ap;
    int count;

    va_start(ap, format);
    count = 0;
    for (int i = 0; *format != '\0'; i++) {
        if (*format == '%') {
            format++;
            count += parcour_flag(*format, ap);
        } else
            count += write(1, format, 1);
        format++;
    }
    va_end(ap);
    return count;
}
