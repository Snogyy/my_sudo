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

int check_password(char *password_hash)
{
    char paswd[64] = { 0 };
    char *salt = strndup(password_hash, 29);
    char *encrypted;

    printf("[my_sudo] password for %s", getenv("USER"));
    disable_echo();
    scanf("%s", paswd);
    enable_echo();
    printf("\n");
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
