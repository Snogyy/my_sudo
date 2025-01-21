/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** Split a string into word
*/

#include "include/my.h"

static int count_space2(char const *str, int k)
{
    for (; str[k] != '\0' && (str[k] == ':' || str[k] == '\n'); k++);
    return k;
}

int count_chara2(char const *str, int *i, int k)
{
    for (*i = 0; str[k] && str[k] != ':' && str[k] != '\n'; *i += 1) {
        k++;
    }
    return k;
}

int function_bizzare2(char const *str, int *k, int count)
{
    if (str[*k] && str[*k] != ':' && str[*k] != '\n') {
        for (; str[*k] != '\0' && (str[*k] == ':' || str[*k] == '\n');
            *k = *k + 1);
        count++;
    }
    return count;
}

int count_word2(char const *str, int count)
{
    int k = 0;

    for (; str[k] != '\0' && (str[k] == ':' || str[k] == '\n'); k++);
    for (; str[k]; k++) {
        count = function_bizzare2(str, &k, count);
    }
    return count + 1;
}

static char *my_str_to_word_array2(char const *str, char **tab, int count)
{
    int i = 0;
    int b = 0;
    int k = 0;

    for (int c = 0; c < count; c++) {
        k = count_space2(str, k);
        count_chara2(str, &i, k);
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

char **separate(char const *str)
{
    int count = 0;
    char **tab;

    count = count_word2(str, count);
    tab = malloc(sizeof(char *) * (count + 1));
    if (tab == NULL)
        return tab;
    my_str_to_word_array2(str, tab, count);
    tab[count] = NULL;
    return tab;
}
