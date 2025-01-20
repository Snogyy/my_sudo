/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** Compare two string
*/

int my_strcmp2(char const *s1, char const *s2, int k, int i)
{
    int e = 0;

    for (e; s1[e] != s1[i] || s2[e] != s2[k]; e++) {
        if (s1[e] < s2[e]) {
            return (-1);
        }
        if (s1[e] > s2[e]) {
            return (1);
        }
    }
    if (e < i) {
        return (1);
    }
    if (e < k) {
        return (-1);
    }
    return 0;
}

int my_strcmp(char const *s1, char const *s2)
{
    int k = 0;
    int i = 0;

    for (i; s1[i] != '\0'; i++);
    for (k; s2[k] != '\0'; k++);
    for (int e = 0; s1[e] == s2[e]; e++) {
        if (s1[e] == s1[i] && s2[e] == s2[k]) {
            return (0);
        }
    }
    return (my_strcmp2(s1, s2, i, k));
}
