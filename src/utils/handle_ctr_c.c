/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctr_c
*/
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "project.h"

void handle_ctr_c(int sig)
{
    if (sig == SIGINT) {
        printf("\n");
        print_prompt();
    }
}
