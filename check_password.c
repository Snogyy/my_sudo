/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** check_password.c
*/

#include "include/my.h"
#include <crypt.h>
#include <string.h>

int check_password(char *password_hash)
{
    char paswd[64] = { 0 };
    char *salt = strndup(password_hash, 29);
    char *encrypted;

    printf("Enter the secret password : ");
    scanf("%s", paswd);
    encrypted = strdup(crypt(paswd, salt));
    if (strcmp(encrypted, password_hash) == 0) {
        free(salt);
        free(encrypted);
        free(password_hash);
        return 1;
    }
    free(salt);
    free(encrypted);
    free(password_hash);
    return 0;
}
