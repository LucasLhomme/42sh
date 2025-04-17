/*
** EPITECH PROJECT, 2025
** 42sh
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
    printf("\033[4m\033[1m\033[92m[%s", user);
    printf("\033[94m@\033[93m%s]\033[92m\033[0m\033[1m\033[92m>\033[37m", dir);
    free_prompt(dir, user);
    return 0;
}
