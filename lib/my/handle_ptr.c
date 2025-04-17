/*
** EPITECH PROJECT, 2024
** handle_ptr
** File description:
** print les coordonnées d'une variable pointeur
*/

#include <stdarg.h>
#include "../../include/my.h"
#include "../../include/structid.h"
#include <stdio.h>

int handle_ptr(va_list ap)
{
    void *ptr = va_arg(ap, void *);
    long int adresse = (unsigned long)ptr;
    char *base = "0123456789abcdef";
    char hex[32];
    int i = 0;

    do {
        hex[i] = base[adresse % 16];
        adresse = adresse / 16;
        i++;
    } while (adresse != 0);
    hex[i] = '\0';
    my_putstr("0x");
    my_revstr(hex);
    my_putstr(hex);
    return 0;
}
