/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** verify_sudoers
*/

#include "include/my.h"

static int fill_auth_group(char **auth_groups, char *line, int index_group)
{
    char e[100];
    char o[100];
    struct group *grp;
    int gid;
    char *group;

    if (sscanf(line, "%s %s", e, o) == 2 && strstr(o, "ALL") && e[0] == '%') {
        auth_groups[index_group] = strdup(e);
        memmove(&auth_groups[index_group][0], &auth_groups[index_group][1],
        strlen(auth_groups[index_group]));
        index_group++;
    }
    if (sscanf(line, "%%#%d %s", &gid, o) == 2 && strstr(o, "ALL")) {
        grp = getgrgid(gid);
        group = grp->gr_name;
        auth_groups[index_group] = strdup(group);
        index_group++;
    }
    return index_group;
}

static int fill_auth_user(char **auth_users, char *line, int index_user)
{
    char e[100];
    char o[100];
    struct passwd *pwd;
    int uid;

    if (sscanf(line, "%s %s", e, o) == 2 && strstr(o, "ALL") && e[0] != '%'
    && e[0] != '#') {
        auth_users[index_user] = strdup(e);
        index_user++;
    }
    if (sscanf(line, "#%d %s", &uid, o) == 2 && strstr(o, "ALL")) {
        auth_users[index_user] = get_user(uid);
        index_user++;
    }
    return index_user;
}

void find_auth(char **auth_groups, char **auth_users)
{
    char l[200];
    int index_group = 0;
    int index_user = 0;
    FILE *file = fopen("/etc/sudoers", "r");

    if (!file)
        exit(84);
    while (fgets(l, sizeof(l), file) != NULL) {
        index_group = fill_auth_group(auth_groups, l, index_group);
        index_user = fill_auth_user(auth_users, l, index_user);
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

int is_sudoer(sudo_t *sudo_struct)
{
    char *user = sudo_struct->user;
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
