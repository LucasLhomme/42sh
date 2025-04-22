/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_setenv.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "project.h"
#include "my.h"

static int is_valid_variable_name(char *var_name, char **args)
{
    if (is_alpha(var_name[0]) == 84) {
        my_putstrerror("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (len_tab(args) >= 3) {
        my_putstrerror("setenv: Too many arguments.\n");
        return 1;
    }
    if (is_alnum_two(var_name) == 84) {
        my_putstrerror("setenv: Variable name must contain ");
        my_putstrerror("alphanumeric characters.\n");
        return 1;
    }
    return 0;
}

static int validate_setenv_args(char **args)
{
    if (args[1] != NULL) {
        if (strchr(args[1], '=') != NULL) {
            my_putstrerror("setenv: Variable name must ");
            my_putstrerror("contain alphanumeric characters.\n");
            return 1;
        }
        if (nb_char(args[1], '.') == 1 || nb_char(args[1], '_') == 1)
            return 1;
        return is_valid_variable_name(args[1], args);
    }
    return 0;
}

static pack_env_t *find_env_variable(env_t *head, char *env_val, char *new_val,
    int len)
{
    int idx_node = 0;
    pack_env_t *pack = malloc(sizeof(pack_env_t));

    if (!pack)
        return NULL;
    while (head) {
        if (my_strncmp(env_val, head->line, len) == 0) {
            pack->line = my_strdup(head->line);
            pack->idx = idx_node;
            pack->env_value = env_val;
            pack->new_value = new_val;
            return pack;
        }
        head = head->next;
        idx_node++;
    }
    free(pack);
    return NULL;
}

static pack_env_t *check_in_env(char **args, char *env_val, char *new_val,
    env_t *head)
{
    int len = my_strlen(env_val);
    int len_args = len_tab(args);

    if (len_args != 2)
        return NULL;
    return find_env_variable(head, env_val, new_val, len);
}

static int initialize_env(env_t **head, char **env)
{
    if (!*head) {
        *head = def_linked_list(env[0], 0, env);
    }
    return (*head == NULL) ? 1 : 0;
}

static int update_existing_env_var(char **args, env_t *head)
{
    pack_env_t *pack = check_in_env(args, args[1], args[2], head);

    if (pack) {
        head = home(head, pack);
        free(pack);
        return 1;
    }
    return 0;
}

static int add_or_update_env_var(char **args, env_t *head)
{
    if (args[2] != NULL) {
        return casual_add(args[1], args[2], head) ? 0 : 1;
    } else {
        if (one_arg(head, args[1]))
            return 0;
        else
            return 1;
    }
}

int my_setenv(char **args, env_t *head, char **env, int *exit_status)
{
    int len_args = len_tab(args);

    (void)exit_status;
    if (initialize_env(&head, env))
        return 1;
    if (my_strcmp(args[0], "setenv") != 0)
        return 0;
    if (len_args == 0) {
        print_list(head);
        return 0;
    }
    if (update_existing_env_var(args, head))
        return 0;
    if (validate_setenv_args(args))
        return 0;
    return (add_or_update_env_var(args, head));
}
