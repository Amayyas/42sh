/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** my_strcmp
*/

/// @brief compare two string
/// @param s1 first string
/// @param s2 second string
/// @return 0, if the string are the same,
/// @return s1[i] - s2[i] if the string are different
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' || s1[i] == '\n')
            return 0;
        i++;
    }
    return (s1[i] - s2[i]);
}
