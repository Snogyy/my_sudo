/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** Do the same as strcat
*/

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int k = 0;

    for (k; dest[k]; k++);
    for (i; src[i]; i++) {
        dest[k + i] = src[i];
    }
    dest[k + i] = '\0';
    return (dest);
}
