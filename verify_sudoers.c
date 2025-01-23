/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** verify_sudoers
*/

#include "include/my.h"

int add_to_group(char **auth_groups, int index_group, char *element)
{
    auth_groups[index_group] = strdup(element);
    memmove(&auth_groups[index_group][0], &auth_groups[index_group][1],
    strlen(auth_groups[index_group]));
    return index_group + 1;
}

void find_auth(char **auth_groups, char **auth_users)
{
    char line[200];
    char element[100];
    char other[100];
    int index_group = 0;
    int index_user = 0;
    FILE *file = fopen("/etc/sudoers", "r");

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s %s", element, other) == 2 && strstr(other, "ALL")
        && element[0] == '%')
            index_group = add_to_group(auth_groups, index_group, element);
        if (sscanf(line, "%s %s", element, other) == 2
        && strstr(other, "ALL") && element[0] != '%') {
            auth_users[index_user] = strdup(element);
            index_user++;
        }
    }
    fclose(file);
    auth_groups[index_group] = NULL;
    auth_users[index_user] = NULL;
}

char **find_groups(char *user)
{
    FILE *groups;
    char buffer[200];
    char *command = malloc(sizeof(char) * (8 + strlen(user)));

    strcpy(command, "groups ");
    strcat(command, user);
    groups = popen(command, "r");
    fgets(buffer, sizeof(buffer), groups);
    buffer[strlen(buffer) + 1] = '\0';
    return my_str_to_word_array(buffer);
}

int verify_group(char **groups, char *auth_group)
{
    for (int j = 0; groups[j] != NULL; j++) {
        if (strcmp(auth_group, groups[j]) == 0)
            return 1;
    }
    return 0;
}

int is_sudoer(void)
{
    char *user = getenv("USER");
    char **groups = find_groups(user);
    char **auth_groups = malloc(sizeof(char *) * 100);
    char **auth_users = malloc(sizeof(char *) * 100);

    find_auth(auth_groups, auth_users);
    for (int i = 0; auth_groups[i] != NULL; i++) {
        if (verify_group(groups, auth_groups[i]) == 1)
            return 1;
    }
    for (int i = 0; auth_users[i] != NULL; i++) {
        if (strcmp(auth_users[i], user) == 0)
            return 1;
    }
    return 0;
}
