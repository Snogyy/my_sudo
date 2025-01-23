/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** sudo_h.h
*/

#ifndef SUDO_H_H_
    #define SUDO_H_H_

typedef struct sudo_s {
    int fd;
    int u;
    char *buffer;
    char **tab;
    char *user;
    int atempt;
} sudo_t;

#endif /* SUDO_H_H_ */
