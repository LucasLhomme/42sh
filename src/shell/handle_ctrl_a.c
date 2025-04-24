/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctrl_a
*/

#include <unistd.h>

int handle_ctrl_a(int *pos)
{
    for (; *pos > 0; (*pos)--)
        write(1, "\033[D", 3);
    return 1;
}