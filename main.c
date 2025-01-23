/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** main.c
*/

#include "include/my.h"

int main(int argc, char **argv)
{
    sudo_t sudo_struct;

    if (argc < 2)
        return 84;
    sudo_struct.user = getenv("USER");
    if (!sudo_struct.user)
        return 84;
    if (is_sudoer() == 0) {
        write(1, sudo_struct.user, strlen(sudo_struct.user));
        write(1, " is not in the sudoers file.\n", 29);
        return 84;
    }
    if (check_password(find_hash(&sudo_struct)) == 1)
        my_exec(argv[1], argv[2]);
    else {
        printf("Acess denied\n");
        return 84;
    }
}
