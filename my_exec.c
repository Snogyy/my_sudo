/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** my_exec.c
*/

#include "include/my.h"

static void my_exec_bis(int i, char **argv)
{
    char command[120] = { 0 };

    for (; argv[i]; i++) {
            strcat(command, argv[i]);
            if (argv[i + 1])
                strcat(command, " ");
    }
    system(command);
}

void my_exec(sudo_t *sudo_struct, char **argv)
{
    if (sudo_struct->atempt != 0)
        printf("You fail your password %d time\n", sudo_struct->atempt);
    if (sudo_struct->u == 1) {
        my_exec_bis(3, argv);
    } else
        my_exec_bis(1, argv);
}
