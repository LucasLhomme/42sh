/*
** EPITECH PROJECT, 2024
** include
** File description:
** include
*/

#ifndef MY_H
    #define MY_H
    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/stat.h>
    #include "struct_word_array.h"
    #include "project.h"

int my_atoi(const char *str);

char *my_strndup(char *str, char *src, int n);

int str_to_digit(const char *str);

int handle_ptr(va_list ap);

int flottant(va_list ap);

int handle_e(va_list ap);

int my_put_unsigned_nbr(unsigned int nb);

int handle_unsigned(va_list ap);

int handle_oct(va_list ap);

int handle_hexmaj(va_list ap);

int handle_hex(va_list ap);

int my_putfloat(float nb);

int handle_char(va_list ap);

int handle_str(va_list ap);

int handle_int(va_list ap);

int percent(va_list ap);

int my_printf(char const *format, ...);

char *copy_word(const char *str, int start, int end);

int is_alnum(char c);

char **my_str_to_word_array(char const *str);

int count_words(const char *str);

void fill_word_array(const char *str, word_array_t *word_array);

int my_strlen(char const *str);

int my_putstr(char const *str);

void my_putchar(char c);

char *my_strcat(char *dest, char const *src);

char *my_strncat(char *dest, char const *src, int nb);

char *concat_params(int argc, char **argv);

int my_show_word_array(char *const *tab);

int my_compute_power_rec(int nb, int p);

int my_compute_square_root(int nb);

int my_find_prime_sup(int nb);

int my_isneg(int nb);

int my_put_nbr(int nb);

void my_swap(int *a, int *b);

int my_getnbr(char const *str);

void my_sort_int_array(int *tab, int size);

char *my_strcpy(char *dest, char const *src);

char *my_strncpy(char *dest, char const *src, int n);

char *my_revstr(char *str);

char *my_strstr(char *str, char const *to_find);

int my_strcmp(char const *s1, char const *s2);

int my_strncmp(char const *s1, char const *s2, int n);

int my_is_prime(int nb);

char *my_strdup(const char *s);

size_t my_strcspn(char const *s1, char const *s2);

char *get_env(const char *var, env_t *head);

int nb_char(char *str, char c);

char *remove_char(char *str, char c);

char *remove_start(char *str, int n);

char *remove_end(char *str, int n);

char get_last_char(char *str);

int len_tab(char **tab);

char *my_strchr(const char *str, char c);

void print_error_reverse(const char *cmd, const char *message, int status);

int is_alnum_two(char *str);

int my_isalnum_char(char c);

int is_alpha(char c);

char *cat_tab(char **tab);

char **my_str_to_word_array_advanced(char *str, char *extra_chars);

#endif
