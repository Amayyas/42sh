/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (i == n - 1)
            return 0;
        if (s1[i] == '\0' || s2[i] == '\0')
            return 0;
        i++;
    }
    return (1);
}
