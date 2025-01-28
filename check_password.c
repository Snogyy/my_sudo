/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** check_password.c
*/

#include "include/my.h"

void disable_echo(void)
{
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enable_echo(void)
{
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

static void free_funct(char *salt, char *encrypted, char *password_hash)
{
    free(salt);
    free(encrypted);
    free(password_hash);
}

int check_password(sudo_t *sudo_struct, char *password_hash)
{
    char paswd[64] = { 0 };
    char *salt = strndup(password_hash, 29);
    char *encrypted;

    while (sudo_struct->atempt != 3) {
        printf("[my_sudo] password for %s: ", sudo_struct->user);
        disable_echo();
        scanf("%s", paswd);
        enable_echo();
        printf("\n");
        encrypted = strdup(crypt(paswd, salt));
        if (strcmp(encrypted, password_hash) == 0) {
            setuid(0);
            free_funct(salt, encrypted, password_hash);
            return 1;
        }
        printf("Sorry, try again. \n");
        sudo_struct->atempt += 1;
    }
    free_funct(salt, encrypted, password_hash);
    return 0;
}
