/*
** EPITECH PROJECT, 2024
** flag "u"
** File description:
** donne nous + de poucentages stpppppp
*/

#include <stdarg.h>
#include "../../include/my.h"

int handle_unsigned(va_list ap)
{
    unsigned int nb = va_arg(ap, unsigned int);

    return my_put_unsigned_nbr(nb);
}
