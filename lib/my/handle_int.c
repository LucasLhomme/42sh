/*
** EPITECH PROJECT, 2024
** handle_int
** File description:
** print un int pour printf
*/

#include <stdarg.h>
#include "../../include/my.h"

int handle_int(va_list ap)
{
    int nbr = va_arg(ap, int);

    return my_put_nbr(nbr);
}
