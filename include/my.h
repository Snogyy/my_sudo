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
#include <pwd.h>

#ifndef MY_H_
    #define MY_H_

int my_exec(sudo_t *sudo_struct, int argc, char **argv, char **env);
int check_password(sudo_t *sudo_struct, char *password_hash);
char *find_hash(sudo_t *sudo_struct);
int is_sudoer(sudo_t *sudo_struct);
char **my_str_to_word_array(char const *str);
char **separate(char const *str);
int execvpe(const char *file, char *const argv[],
    char *const envp[]);
int my_getgid(char *group);
char *get_user(int uid);
int my_getuid(char *user);
sudo_t *find_gid(char *user, sudo_t *sudo_struct);
int user_in_group(char **list_users, char *user);
int my_getgid_bis(char *user);

#endif
