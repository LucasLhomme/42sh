/*
** EPITECH PROJECT, 2024
** structhandle
** File description:
** structure pour tab de handle
*/

#ifndef STRUCTID_H
    #define STRUCTID_H

typedef struct {
    char symbol;
    int (*handler)(va_list ap);
} format_t;

#endif
