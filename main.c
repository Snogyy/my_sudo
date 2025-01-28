/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** main.c
*/

#include "include/my.h"

static int flag(int argc, char **argv, sudo_t *sudo_struct)
{
    if (argc < 2)
        return 84;
    if (strcmp(argv[1], "-u") == 0) {
        sudo_struct->user = argv[2];
        sudo_struct->u = 1;
    } else {
        sudo_struct->user = getenv("USER");
        sudo_struct->u = 0;
    }
    if (!sudo_struct->user)
        return 84;
    sudo_struct->atempt = 0;
    return 0;
}

int main(int argc, char **argv, char **env)
{
    sudo_t sudo_struct;
    char *hash;

    if (flag(argc, argv, &sudo_struct))
        return 84;
    if (is_sudoer(&sudo_struct) == 0) {
        write(1, sudo_struct.user, strlen(sudo_struct.user));
        write(1, " is not in the sudoers file.\n", 29);
        return 84;
    }
    hash = find_hash(&sudo_struct);
    if (!hash)
        return 84;
    if (check_password(&sudo_struct, hash) == 1)
        return (my_exec(&sudo_struct, argv, env));
    else {
        printf("my_sudo: 3 incorrect password attemps\n");
        return 84;
    }
    return 0;
}
