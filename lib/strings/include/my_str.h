/*
** EPITECH PROJECT, 2022
** my_str.h
** File description:
** my_str.h
*/

#ifndef MY_STR_H_
    #define MY_STR_H_
    #define ABS(nb) ((nb) < 0 ? -(nb) : (nb))
    /**
     * @brief return 1 if the two strings are equal, 0 otherwise.
     * Doesn't work with NULL
     * @param a the first string
     * @param b the second string
     */
    #define fast_strcmp(a, b) ((*(a) == *(b)) && !my_strcmp((a), (b)))

    int my_getnbr(const char *str);
    int my_nbrlen(long long n);
    void my_put_nbr(long long nb);
    void my_putchar(char c);
    int my_str_tablen(char **tab);
    char *my_strcat(char *dest, char const *src);
    int my_strcmp(char const *s1, char const *s2);
    char *my_strcpy(char *dest, char const *src);
    int my_strlen(char const *str);
    char **str_to_word_array(char *str, char *sep);

#endif /* !MY_STR_H_ */
