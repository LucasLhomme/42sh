/*
** EPITECH PROJECT, 2025
** 32sh
** File description:
** print prompt before the getline
*/

#include "my.h"
#include "project.h"
#include <sys/types.h>

static char *extract_username(char *line, int uid)
{
    char *username = strtok(line, ":");
    char *uid_str = NULL;

    strtok(NULL, ":");
    uid_str = strtok(NULL, ":");
    if (uid_str != NULL && atoi(uid_str) == uid)
        return username;
    return NULL;
}

static char *get_username(int uid)
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

static void free_prompt(char *dir, char *user)
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
    my_printf("\033[94m@\033[93m%s]\033[92m\033[0m\033[1m\033[92m ", dir);
    my_printf("\033[0m");
    free_prompt(dir, user);
    return 0;
}

void setup_header_col(const char **col)
{
    col[0] = "\033[0m";
    col[1] = "\033[32m";
    col[2] = "\033[33m";
    col[3] = "\033[34m";
}

static void print_header_part1(const char **col)
{
    printf("%s___________%s/\\\\\\%s_______%s/\\\\\\\\\\\\\\\\\\\\%s________",
        col[1], col[2], col[1], col[2], col[1]);
    printf("%s/\\\\\\\\\\\\\\\\\\\\\\%s____%s/\\\\\\%s________%s/\\\\\\%s_\n",
        col[3], col[1], col[3], col[1], col[3], col[1]);
    printf(" %s_________%s/\\\\\\\\\\%s_____%s/\\\\\\///////\\\\\\%s_____",
        col[1], col[2], col[1], col[2], col[1]);
    printf("%s/\\\\\\/////////\\\\\\%s_%s\\/\\\\\\%s_______%s\\/\\\\\\%s_\n",
        col[3], col[1], col[3], col[1], col[3], col[1]);
    printf("  %s_______%s/\\\\\\/\\\\\\%s____%s\\///%s______%s\\//\\\\\\%s___",
        col[1], col[2], col[1], col[2], col[1], col[2], col[1]);
}

static void print_header_part2(const char **col)
{
    printf("%s\\//\\\\\\%s______%s\\///%s", col[3], col[1], col[3], col[1]);
    printf("__%s\\/\\\\\\%s_______%s\\/\\\\\\%s_\n", col[3], col[1], col[3],
        col[1]);
    printf("   %s_____%s/\\\\\\/\\/\\\\\\%s", col[1], col[2], col[1]);
    printf("_____________%s/\\\\\\/%s_____", col[2], col[1]);
    printf("%s\\////\\\\\\%s__________%s", col[3], col[1], col[3]);
    printf("\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\%s_\n", col[1]);
    printf("    %s___%s/\\\\\\/%s__%s", col[1], col[2], col[1], col[2]);
    printf("\\/\\\\\\%s__________%s/\\\\\\//%s__________", col[1], col[2],
        col[1]);
    printf("%s\\////\\\\\\%s_______%s\\/\\\\\\/////////\\\\\\%s_\n",
        col[3], col[1], col[3], col[1]);
}

static void print_header_part3(const char **col)
{
    printf("     %s_%s/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\", col[1], col[2]);
    printf("%s_____%s/\\\\\\//%s_______________", col[1], col[2], col[1]);
    printf("%s\\////\\\\\\\\%s____%s\\/\\\\\\%s_______%s\\/\\\\\\%s_\n",
        col[3], col[1], col[3], col[1], col[3], col[1]);
    printf("      %s_%s\\///////////\\\\\\/%s____%s/\\\\\\/%s___________",
        col[1], col[2], col[1], col[2], col[1]);
    printf("%s/\\\\\\%s______%s\\//\\\\\\%s",
        col[3], col[1], col[3], col[1]);
}

static void print_header_part4(const char **col)
{
    printf("___%s\\/\\\\\\%s_______%s\\/\\\\\\%s_\n", col[3], col[1], col[3],
        col[1]);
    printf("       %s__________%s\\/\\\\\\%s_____%s",
        col[1], col[2], col[1], col[2]);
    printf("/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\%s_", col[1]);
    printf("%s\\///\\\\\\\\\\\\\\\\\\/_%s__%s", col[3], col[1], col[3]);
    printf("\\/\\\\\\%s_______%s\\/\\\\\\%s_\n", col[1], col[3], col[1]);
    printf("        %s__________%s\\///%s_____%s\\///////////////%s____",
        col[1], col[2], col[1], col[2], col[1]);
    printf("%s\\///////////%s_____%s\\///%s________%s\\///%s__%s\n",
        col[3], col[1], col[3], col[1], col[3], col[1], col[3]);
    printf("%s", col[0]);
}

void print_header(void)
{
    const char *col[4];

    setup_header_col(col);
    print_header_part1(col);
    print_header_part2(col);
    print_header_part3(col);
    print_header_part4(col);
}
