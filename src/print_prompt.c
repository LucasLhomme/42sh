/*
** EPITECH PROJECT, 2025
** 32sh
** File description:
** print prompt before the getline
*/

#include "my.h"
#include "project.h"
#include <sys/types.h>

char *extract_username(char *line, int uid)
{
    char *username = strtok(line, ":");
    char *uid_str = NULL;

    strtok(NULL, ":");
    uid_str = strtok(NULL, ":");
    if (uid_str != NULL && atoi(uid_str) == uid)
        return username;
    return NULL;
}

char *get_username(int uid)
{
    FILE *file = fopen("/etc/passwd", "r");
    char line[256];
    char *username;
    char *result = NULL;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        username = extract_username(line, uid);
        if (username != NULL) {
            result = strdup(username);
            break;
        }
    }
    fclose(file);
    return result;
}

void free_prompt(char *dir, char *user)
{
    free(dir);
    free(user);
}

int print_prompt(void)
{
    uid_t uid = getuid();
    char *user = get_username(uid);
    char *dir = getcwd(NULL, 0);

    if (!user || !dir)
        return 84;
    my_printf("\033[4m\033[1m\033[92m[%s", user);
    my_printf("\033[94m@\033[93m%s]\033[92m\033[0m\033[1m\033[92m>\033[0m", dir);
    free_prompt(dir, user);
    return 0;
}

void print_header(void)
{
    const char *reset = "\033[0m";

    printf("\033[32m____________\033[33m/\\\\\\\033[32m_______\033[33m/\\\\\\\\\\\\\\\\\\\\\033[32m________\033[34m/\\\\\\\\\\\\\\\\\\\\\\\033[32m____\033[34m/\\\\\\\033[32m________\033[34m/\\\\\\\033[32m_\n");
    printf(" \033[32m__________\033[33m/\\\\\\\\\\\033[32m_____\033[33m/\\\\\\///////\\\\\\\033[32m_____\033[34m/\\\\\\/////////\\\\\\\033[32m_\033[34m\\/\\\\\\\033[32m_______\033[34m\\/\\\\\\\033[32m_\n");
    printf("  \033[32m________\033[33m/\\\\\\/\\\\\\\033[32m____\033[33m\\///\033[32m______\033[33m\\//\\\\\\\033[32m___\033[34m\\//\\\\\\\033[32m______\033[34m\\///\033[32m__\033[34m\\/\\\\\\\033[32m_______\033[34m\\/\\\\\\\033[32m_\n");
    printf("   \033[32m______\033[33m/\\\\\\/\\/\\\\\\\033[32m______________\033[33m/\\\\\\/\033[32m_____\033[34m\\////\\\\\\\033[32m_________\033[34m\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\033[32m_\n");
    printf("    \033[32m____\033[33m/\\\\\\/\033[32m__\033[33m\\/\\\\\\\033[32m___________\033[33m/\\\\\\//\033[32m__________\033[34m\\////\\\\\\\033[32m______\033[34m\\/\\\\\\/////////\\\\\\\033[32m_\n");
    printf("     \033[32m__\033[33m/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\033[32m_____\033[33m/\\\\\\//\033[32m________________\033[34m\\////\\\\\\\\\033[32m___\033[34m\\/\\\\\\\033[32m_______\033[34m\\/\\\\\\\033[32m_\n");
    printf("      \033[32m_\033[33m\\///////////\\\\\\//\033[32m____\033[33m/\\\\\\/\033[32m____________\033[34m/\\\\\\\033[32m______\033[34m\\//\\\\\\\033[32m__\033[34m\\/\\\\\\\033[32m_______\033[34m\\/\\\\\\\033[32m_\n");
    printf("       \033[32m___________\033[33m\\/\\\\\\\033[32m_____\033[33m/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\033[32m_\033[34m\\///\\\\\\\\\\\\\\\\\\/\033[32m___\033[34m\\/\\\\\\\033[32m_______\033[34m\\/\\\\\\\033[32m_\n");
    printf("        \033[32m___________\033[33m\\///\033[32m_____\033[33m\\///////////////\033[32m____\033[34m\\///////////\033[32m_____\033[34m\\///\033[32m________\033[34m\\///\033[32m__\033[34m\n");
    printf("%s", reset);
}
