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
    char *user = getenv("USER");

    if (argc < 3)
        return 84;
    if (is_sudoer() == 0) {
        write(1, user, strlen(user));
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
