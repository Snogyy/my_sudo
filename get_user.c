/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** get_user.c
*/

#include "include/my.h"

char *get_user(void)
{
    FILE *fd;
    char buff[512];
    char asker_name[256];
    char pass[256];
    int asker_uid;

    fd = fopen("/etc/passwd", "r");
    while (fgets(buff, sizeof(buff), fd)) {
        sscanf(buff, "%31[^:]:%31[^:]:%d:", asker_name, pass, &asker_uid);
        if (asker_uid == getuid())
            break;
    }
    fclose(fd);
    return strdup(asker_name);
}