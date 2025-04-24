/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctrl_l
*/
#include <unistd.h>
#include "project.h"

int handle_ctrl_l(char *line, int *pos, int *len)
{
    write(1, "\033[H\033[J", 6);
    *pos = 0;
    *len = 0;
    line[0] = '\0';
    print_prompt();
    return 1;
}