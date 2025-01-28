/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** my_getuid
*/

#include "include/my.h"

int str_to_int(char *str)
{
    int res = 0;

    for (int i = 0; i < strlen(str); i++)
        res = (res * 10) + str[i] - 48;
    return res;
}

int my_getuid(char *user)
{
    char line[200];
    char **tab;
    FILE *file = fopen("/etc/passwd", "r");
    int result;

    while (fgets(line, sizeof(line), file) != NULL) {
        tab = separate(line);
        if (strcmp(tab[0], user) == 0)
            return str_to_int(tab[2]);
    }
    return 84;
}

int my_getgid(char *user)
{
    char line[200];
    char **tab;
    FILE *file = fopen("/etc/passwd", "r");
    int result;

    while (fgets(line, sizeof(line), file) != NULL) {
        tab = separate(line);
        if (strcmp(tab[0], user) == 0)
            return str_to_int(tab[3]);
    }
    return 84;
}
