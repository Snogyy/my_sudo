/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** my_exec.c
*/

#include "include/my.h"

static int my_exec_bis(int i, char **argv, char **env)
{
    if (setuid(my_getuid_root()) == -1)
        printf("Error setuid\n");
    return (execvpe(argv[i], &argv[i], env));
}

int my_exec(sudo_t *sudo_struct, char **argv, char **env)
{
    int rep = 0;

    if (sudo_struct->atempt != 0)
        printf("You fail your password %d time\n", sudo_struct->atempt);
    if (sudo_struct->u == 1) {
        rep = my_exec_bis(3, argv, env);
    } else
        rep = my_exec_bis(1, argv, env);
    return rep;
}
