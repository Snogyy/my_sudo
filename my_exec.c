/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** my_exec.c
*/

#include "include/my.h"

static int my_exec_bis(int argc, char **argv, char **env)
{
    int i;

    if (argc > 2 && strcmp(argv[1], "-u") == 0) {
        i = 3;
        if (my_getuid(argv[2]) == 84 || setuid(my_getuid(argv[2])) == -1)
            return 84;
    } else {
        i = 1;
        if (setuid(my_getuid("root") == -1))
            return 84;
    }
    printf("%d\n", execvpe(argv[i], &argv[i], env));
    return (execvpe(argv[i], &argv[i], env));
}

int my_exec(sudo_t *sudo_struct, int argc, char **argv, char **env)
{
    int rep = 0;

    if (sudo_struct->atempt != 0)
        printf("You fail your password %d time\n", sudo_struct->atempt);
    rep = my_exec_bis(argc, argv, env);
    if (rep == -1)
        return 84;
    return rep;
}
