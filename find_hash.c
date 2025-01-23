/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** find_hash.c
*/

#include "include/my.h"

static void free_function(sudo_t *sudo_struct)
{
    free(sudo_struct->buffer);
    close(sudo_struct->fd);
    for (int i = 0; sudo_struct->tab[i]; i++)
        free(sudo_struct->tab[i]);
    free(sudo_struct->tab);
}

static char *find_hash_bis(sudo_t *sudo_strct)
{
    char *hash = NULL;

    for (int i = 0; sudo_strct->tab[i]; i++) {
        if (strcmp(sudo_strct->tab[i], sudo_strct->user) == 0)
            hash = strdup(sudo_strct->tab[i + 1]);
    }
    free_function(sudo_strct);
    return hash;
}

char *find_hash(sudo_t *sudo_struct)
{
    struct stat sd;

    sudo_struct->fd = open(SHADOW, O_RDONLY);
    if (!sudo_struct->fd)
        return NULL;
    stat(SHADOW, &sd);
    sudo_struct->buffer = malloc(sizeof(char) * sd.st_size + 1);
    if (!sudo_struct->buffer)
        return NULL;
    read(sudo_struct->fd, sudo_struct->buffer, sd.st_size);
    sudo_struct->buffer[sd.st_size] = '\0';
    sudo_struct->tab = separate(sudo_struct->buffer);
    return find_hash_bis(sudo_struct);
}
