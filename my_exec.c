/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** my_exec.c
*/

#include "include/my.h"

static int my_exec_bis(sudo_t *sudo_struct, char **argv, char **env)
{
    int i = 0;

    if (sudo_struct->u != 0) {
        if (my_getuid(argv[sudo_struct->u + 1]) == 84 ||
            setuid(my_getuid(argv[sudo_struct->u + 1])) == -1)
            return 84;
        i = 1;
    } else {
        if (setuid(my_getuid("root")) == -1 || setgid(my_getgid("root")) == -1)
            return 84;
    }
    return (execvpe(sudo_struct->command[i], &sudo_struct->command[i], env));
}

int my_exec(sudo_t *sudo_struct, int argc, char **argv, char **env)
{
    int rep = 0;

    if (sudo_struct->atempt != 0)
        printf("You fail your password %d time\n", sudo_struct->atempt);
    rep = my_exec_bis(sudo_struct, argv, env);
    free(sudo_struct->command);
    if (rep == -1)
        return 84;
    return rep;
}
