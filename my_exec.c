/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** my_exec.c
*/

#include "include/my.h"

void my_exec(char *arg0, char *arg1)
{
    execlp(arg0, arg0, arg1, NULL);
}
