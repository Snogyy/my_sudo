/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** get_user.c
*/

#include "include/my.h"

char *get_user(void)
{
    int fd = open(PASSWD, O_RDONLY);
    struct stat sd;
    char **tab = NULL;
    char *temp = NULL;
    int nDigits = 0;
    char *rep = NULL;
    char *buffer = NULL;

    if (!fd)
        return NULL;
    stat(PASSWD, &sd);
    buffer = malloc(sizeof(char) * sd.st_size + 1);
    if (!buffer)
        return NULL;
    read(fd, buffer, sd.st_size);
    buffer[sd.st_size] = '\0';
    tab = separate(buffer);
    for (int i = 0; tab; i++) {
        nDigits = floor(log10(abs((int)getuid()))) + 1;
        temp = malloc(sizeof(char) * nDigits + 1);
        sprintf(temp, "%d", (int)getuid());
        temp[nDigits] = '\0';
        if (i % 7 == 0 && strcmp(temp, tab[i]) == 0) {
            rep = strdup(tab[i - 3]);
            break;
        }
        free(temp);
    }
    free(temp);
    free(buffer);
    close(fd);
    return rep;
}