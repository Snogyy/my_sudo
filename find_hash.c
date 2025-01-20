/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** find_hash.c
*/

#include "include/my.h"

static void free_function(sudo_t *sudo_struct)
{
    free(sudo_struct->buffer2);
    free(sudo_struct->buffer);
    close(sudo_struct->fd);
    close(sudo_struct->fd2);
    for (int i = 0; sudo_struct->tab[i]; i++)
        free(sudo_struct->tab[i]);
    free(sudo_struct->tab);
    for (int i = 0; sudo_struct->tab2[i]; i++)
        free(sudo_struct->tab2[i]);
    free(sudo_struct->tab2);
    free(sudo_struct->rep);
}

static char *find_hash_bis(sudo_t *sudo_strct)
{
    char *hash = NULL;

    for (int i = 0; sudo_strct->tab2[i]; i++) {
        sudo_strct->nDigits = floor(log10(abs((int)getuid()))) + 1;
        sudo_strct->temp = malloc(sizeof(char) * sudo_strct->nDigits + 1);
        sprintf(sudo_strct->temp, "%d", (int)getuid());
        sudo_strct->temp[sudo_strct->nDigits] = '\0';
        if (i % 7 == 0 && strcmp(sudo_strct->temp, sudo_strct->tab2[i]) == 0) {
            sudo_strct->rep = strdup(sudo_strct->tab2[i - 3]);
            free(sudo_strct->temp);
            break;
        }
        free(sudo_strct->temp);
    }
    for (int i = 0; sudo_strct->tab[i]; i++) {
        if (strcmp(sudo_strct->tab[i], sudo_strct->rep) == 0)
            hash = strdup(sudo_strct->tab[i + 1]);
    }
    free_function(sudo_strct);
    return hash;
}

char *find_hash(sudo_t *sudo_struct)
{
    struct stat sd;
    struct stat sb;

    sudo_struct->fd = open(SHADOW, O_RDONLY);
    sudo_struct->fd2 = open(PASSWD, O_RDONLY);
    if (!sudo_struct->fd || !sudo_struct->fd2)
        return NULL;
    stat(SHADOW, &sd);
    stat(PASSWD, &sb);
    sudo_struct->buffer = malloc(sizeof(char) * sd.st_size + 1);
    sudo_struct->buffer2 = malloc(sizeof(char) * sb.st_size + 1);
    if (!sudo_struct->buffer || !sudo_struct->buffer2)
        return NULL;
    read(sudo_struct->fd, sudo_struct->buffer, sd.st_size);
    read(sudo_struct->fd2, sudo_struct->buffer2, sb.st_size);
    sudo_struct->buffer[sd.st_size] = '\0';
    sudo_struct->buffer2[sb.st_size] = '\0';
    sudo_struct->tab = separate(sudo_struct->buffer);
    sudo_struct->tab2 = separate(sudo_struct->buffer2);
    return find_hash_bis(sudo_struct);
}
