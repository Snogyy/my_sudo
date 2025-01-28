/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** my_getuid
*/

#include "include/my.h"

int str_to_int(char *str)
{
    int result = str[0] - 48;

    for (int i = 1; str[i] != '\0'; i++) {
        result *= 10;
        result = str[i] - 48;
    }
    return result;
}

int my_getuid_root(void)
{
    char line[200];
    char **tab;
    FILE *file = fopen("/etc/passwd", "r");
    int result;

    while (fgets(line, sizeof(line), file) != NULL) {
        tab = separate(line);
        if (strcmp(tab[0], "root") == 0)
            return str_to_int(tab[2]);
    }
}
