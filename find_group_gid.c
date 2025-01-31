/*
** EPITECH PROJECT, 2024
** B-PSU-100-STG-1-1-mysudo-jules.nourdin
** File description:
** find_group_gid.c
*/

#include "include/my.h"

sudo_t *find_gid(char *user, sudo_t *sudo_struct)
{
    FILE *group_file = fopen("/etc/group", "r");
    gid_t *gid = malloc(sizeof(gid_t) * 100);
    int actgid = 0;
    char line[1000];
    char usr_l[500];
    char **list_users;
    int index = 0;

    while (fgets(line, sizeof(line), group_file) != NULL) {
        if (sscanf(line, "%*99[^:]:%*c:%d:%499[^\n]", &actgid, usr_l) < 3)
            continue;
        list_users = my_str_to_word_array(usr_l);
        if (user_in_group(list_users, user) == 1) {
            gid[index] = (gid_t) actgid;
            index++;
        }
    }
    sudo_struct->gid = gid;
    sudo_struct->nbrg = index;
    return sudo_struct;
}
