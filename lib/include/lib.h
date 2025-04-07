/*
** EPITECH PROJECT, 2024
** Mon H
** File description:
** Header avec les fonctions
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#ifndef LIB_H
    #define LIB_H
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strstr(char *str, char const *to_find);
int my_strncmp(char const *s1, char const *s2, size_t n);
char *my_revstr(char *str);
void my_putchar(char c);
int my_print_comb2(void);
void print_comb(int nb1, int nb2);
int my_getnbr(char const *str);
int my_evil_str(char *str);
int my_print_comb(void);
int sort_params(int argc, char *argv[]);
char *my_strdup(char const *src);
char *my_revstr(char *str);
void my_swap(int *a, int *b);
char *my_strstr(char *str, char const *to_find);
char **my_str_to_word_array(char const *str);
char *my_strndup(const char *str, size_t n);
int my_printf(const char *format, ...);
void flag_o(va_list list);
void flag_d(va_list list);
void flag_s(va_list list);
void flag_i(va_list list);
void flag_c(va_list list);
void flag_percent(va_list list);
void flag_x2(va_list list);
void flag_x(va_list list);
void blank(va_list list);
int my_isalpha(char c);
int my_strcmp(char const *s1, char const *s2);
int flag_detector(const char *format, int i, va_list list);
int isalphanum(char c);
char *my_strcat(char *str, const char *new_str);
int my_isalpha(char c);
int my_isnum(char c);
char *my_uppercase(char *str);
int nonalphanum(char c);
char **my_str_to_word_array_advanced(char *str, char *extra_chars);
char *my_strtok(char *str, const char *delim);
char *my_strchr(const char *str, char c);
char *trim_whitespace(char *str);
int my_isspace(char c);

#endif /*lib.h*/
