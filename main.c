/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** main.c
*/

#include "include/my.h"

static void flag(char **argv, sudo_t *sudo_struct)
{
    if (strcmp(argv[1], "-u") == 0) {
        sudo_struct->user = argv[2];
        sudo_struct->u = 1;
    } else {
        sudo_struct->user = getenv("USER");
        sudo_struct->u = 0;
    }
    sudo_struct->atempt = 0;
}

int main(int argc, char **argv)
{
    sudo_t sudo_struct;
    char *hash;

    if (argc < 2)
        return 84;
    flag(argv, &sudo_struct);
    if (!sudo_struct.user)
        return 84;
    if (is_sudoer() == 0) {
        write(1, sudo_struct.user, strlen(sudo_struct.user));
        write(1, " is not in the sudoers file.\n", 29);
        return 84;
    }
    hash = find_hash(&sudo_struct);
    if (!hash)
        return 84;
    if (check_password(&sudo_struct, hash) == 1)
        my_exec(&sudo_struct, argv);
    else
        return 84;
}
