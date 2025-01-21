/*
** EPITECH PROJECT, 2024
** my
** File description:
** contain the prototype of all the function in libmy.a
*/

#include "sudo_h.h"
#include "macro.h"
#include <math.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/sysmacros.h>
#include <stdbool.h>
#include <crypt.h>
#include <termios.h>

#ifndef MY_H_
    #define MY_H_

void my_exec(char *arg0, char *arg1);
int check_password(char *password_hash);
char *find_hash(sudo_t *sudo_struct);
int is_sudoer(void);
char **my_str_to_word_array(char const *str);
char **separate(char const *str);

#endif
