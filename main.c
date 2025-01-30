/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-bsmysudo-esteban.munier
** File description:
** main.c
*/

#include "include/my.h"

static sudo_t *init_struct(int argc, sudo_t *sudo_struct)
{
    sudo_struct->user = get_user((int)getuid());
    sudo_struct->atempt = 0;
    sudo_struct->h = 0;
    sudo_struct->command = malloc(sizeof(char *) * (argc + 1));
    if (!sudo_struct->command)
        return NULL;
    for (int i = 0; i <= argc; i++)
        sudo_struct->command[i] = NULL;
    sudo_struct->u = 0;
    sudo_struct->g = 0;
    sudo_struct->E = 0;
    sudo_struct->s = 0;
    return sudo_struct;
}

int check_user(char *user)
{
    if (my_getuid(user) == 84) {
        printf("my_sudo: uknown user %s\n", user);
        return 84;
    }
    return 0;
}

int check_group(char *group)
{
    if (my_getgid(group) == 84) {
        printf("my_sudo: uknown group %s\n", group);
        return 84;
    }
    return 0;
}

static sudo_t **set_flag(int i, char **argv, sudo_t **sudo_struct)
{
    if (strcmp(argv[i], "-h") == 0) {
        printf("usage: ./my_sudo -h\nusage: ./my_sudo"
        "[-ugEs] [command [args ...]]\n");
        (*sudo_struct)->h = i;
    }
    if (strcmp(argv[i], "-u") == 0) {
        (*sudo_struct)->u = i;
        if (check_user(argv[i + 1]) == 84 || argv[i + 1] == NULL)
            return NULL;
    }
    if (strcmp(argv[i], "-g") == 0) {
        (*sudo_struct)->g = i;
        if (check_group(argv[i + 1]) == 84)
            return NULL;
    }
    if (strcmp(argv[i], "-E") == 0)
        (*sudo_struct)->E = i;
    if (strcmp(argv[i], "-s") == 0)
        (*sudo_struct)->s = i;
    return sudo_struct;
}

static int check_flag(int i, char **argv, sudo_t **sudo_struct)
{
    char *flag = "hugEs";
    int b = 84;

    for (int j = 0; flag[j]; j++) {
        if (argv[i][1] == flag[j]) {
            b = 0;
            sudo_struct = set_flag(i, argv, sudo_struct);
        }
        if (!sudo_struct)
            return 84;
    }
    return b;
}

static int flag(int argc, char **argv, sudo_t *sudo_struct)
{
    int b = 0;
    int k = 0;

    if (argc < 2) {
        printf("usage: ./my_sudo -h\nusage: ./my_sudo"
        "[-ugEs] [command [args ...]]\n");
        return 84;
    }
    sudo_struct = init_struct(argc, sudo_struct);
    if (!sudo_struct)
        return 84;
    for (int i = 1; argv[i] != NULL; i++) {
        if (argv[i][0] == '-') {
            b = check_flag(i, argv, &sudo_struct);
            i += 1;
        } else {
            sudo_struct->command[k] = strdup(argv[i]);
            k++;
        }
        if (b == 84)
            return 84;
    }
    return 0;
}

static void free_struct(sudo_t *sudo_struct)
{
    for (int i = 0; sudo_struct->command[i] != NULL; i++) {
            free(sudo_struct->command[i]);
            sudo_struct->command[i] = NULL;
    }
    if (sudo_struct->command)
        free(sudo_struct->command);
    if (sudo_struct->user)
        free(sudo_struct->user);
    sudo_struct->user = NULL;
    sudo_struct->command = NULL;
}

int false_sudoer(sudo_t *sudo_struct)
{
    write(1, sudo_struct->user, strlen(sudo_struct->user));
    write(1, " is not in the sudoers file.\n", 29);
    free_struct(sudo_struct);
    return 84;
}

int my_sudo(sudo_t *sudo_struct, int argc, char **argv, char **env)
{
    char *hash = NULL;

    hash = find_hash(sudo_struct);
    if (!hash) {
        free_struct(sudo_struct);
        return 84;
    }
    if (check_password(sudo_struct, hash) == 1) {
        if (is_sudoer(sudo_struct) == 0)
            return false_sudoer(sudo_struct);
        return (my_exec(sudo_struct, argc, argv, env));
    } else {
        printf("my_sudo: 3 incorrect password attempts\n");
        free_struct(sudo_struct);
        return 84;
    }
    free_struct(sudo_struct);
    if (sudo_struct->E == 0)
        clearenv();
    return 0;
}

int main(int argc, char **argv, char **env)
{
    sudo_t sudo_struct = { 0 };

    if (flag(argc, argv, &sudo_struct) == 84)
        return 84;
    if (sudo_struct.h != 0)
        return 0;
    return my_sudo(&sudo_struct, argc, argv, env);
}
