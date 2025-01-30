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

int user_in_group(char **list_users, char *user)
{
    for (int i = 0; list_users[i] != NULL; i++) {
        if (strcmp(list_users[i], user) == 0)
            return 1;
    }
    return 0;
}

char **find_groups(char *user)
{
    FILE *group_file = fopen("/etc/group", "r");
    char line[1000];
    char act_group[100];
    char user_line[500];
    char **list_users;
    char **list_groups = malloc(sizeof(char *) * 100);
    int index = 0;

    while (fgets(line, sizeof(line), group_file) != NULL) {
        if (sscanf(line, "%99[^:]:%*c:%*d:%499[^\n]",
        act_group, user_line) < 2)
            continue;
        list_users = my_str_to_word_array(user_line);
        if (user_in_group(list_users, user) == 1) {
            list_groups[index] = strdup(act_group);
            index++;
        }
    }
    list_groups[index] = NULL;
    return list_groups;
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
