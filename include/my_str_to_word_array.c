/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Split a string into word
*/

#include "my.h"

int count_spaces(char const *str, int k)
{
    for (; str[k] != '\0' && !(((str[k] >= '0') && (str[k] <= '9')) ||
    ((str[k] >= 'a') && (str[k] <= 'z')) ||
    ((str[k] >= 'A') && (str[k] <= 'Z')) || str[k] == '.'); k++);
    return k;
}

int count_char(char const *str, int *i, int k)
{
    for (*i = 0; (((str[k] >= '0') && (str[k] <= '9')) ||
    ((str[k] >= 'a') && (str[k] <= 'z')) ||
    ((str[k] >= 'A') && (str[k] <= 'Z')) || str[k] == '.'); *i += 1) {
        k++;
    }
    return k;
}

int function_bizzare(char const *str, int *k, int count)
{
    if ((str[*k] < '0' || str[*k] > '9') &&
    (str[*k] < 'A' || str[*k] > 'Z') &&
    (str[*k] < 'a' || str[*k] > 'z') && str[*k] != '.') {
        for (; str[*k] != '\0' && !(((str[*k] >= '0') && (str[*k] <= '9')) ||
        ((str[*k] >= 'a') && (str[*k] <= 'z')) ||
        ((str[*k] >= 'A') && (str[*k] <= 'Z'))); *k = *k + 1);
        count++;
    }
    return count;
}

int count_word(char const *str, int count)
{
    int j = 0;
    int k = 0;

    for (; str[k] != '\0' && !(((str[k] >= '0') && (str[k] <= '9')) ||
        ((str[k] >= 'a') && (str[k] <= 'z')) ||
        ((str[k] >= 'A') && (str[k] <= 'Z')) || str[k] == '.'); k++);
    for (; str[k]; k++) {
        count = function_bizzare(str, &k, count);
    }
    return count + 1;
}

static char *my_str_to_word_array_bis(char const *str, char **tab, int count)
{
    int i = 0;
    int b = 0;
    int k = 0;

    for (int c = 0; c < count; c++) {
        k = count_spaces(str, k);
        count_char(str, &i, k);
        tab[c] = malloc(sizeof(char) * (i + 1));
        if (tab[c] == NULL)
            return tab[c];
        for (b = 0; b < i; b++) {
            tab[c][b] = str[k];
            k++;
        }
        tab[c][b] = '\0';
    }
    return NULL;
}

char **my_str_to_word_array(char const *str)
{
    int count = 0;
    char **tab;

    count = count_word(str, count);
    tab = malloc(sizeof(char *) * (count + 1));
    if (tab == NULL)
        return tab;
    my_str_to_word_array_bis(str, tab, count);
    tab[count] = NULL;
    return tab;
}
