/*
** EPITECH PROJECT, 2024
** .h
** File description:
** struct
*/

#include <stdlib.h>
#include <stdarg.h>
#include "lib.h"

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct flag_s {
    char flag;
    void (*flag_identifier)(va_list list);
} flag_t;
#endif
