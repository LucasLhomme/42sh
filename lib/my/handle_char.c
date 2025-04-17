/*
** EPITECH PROJECT, 2024
** handle_char
** File description:
** print les char pour printf
*/

#include <stdarg.h>
#include "../../include/my.h"

int handle_char(va_list ap)
{
    char c = (char)va_arg(ap, int);

    my_putchar(c);
    return 1;
}
