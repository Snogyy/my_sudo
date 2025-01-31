/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** sudo_h.h
*/

#include <grp.h>
#ifndef SUDO_H_H_
    #define SUDO_H_H_

typedef struct sudo_s {
    int fd;
    int u;
    int g;
    int s;
    int h;
    int E;
    char *buffer;
    char **tab;
    char **command;
    char *user;
    gid_t *gid;
    int nbrg;
    int atempt;
} sudo_t;

#endif /* SUDO_H_H_ */
