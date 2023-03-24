/*
** EPITECH PROJECT, 2023
** B-MUL-200-TLS-2-1-mypaint-theodore.magna [WSL: fedora]
** File description:
** errorhandling
*/

#ifndef ERRORHANDLING_H_
    #define ERRORHANDLING_H_
    #define ERROR 84
    #define SUCCESS 0
    #define UNUSED __attribute__((unused))
    #define DEPRECATED __attribute__((deprecated))
    #define ASSERT_MALLOC(ptr, retrn) if (ptr == ((void *)0)) return retrn;

#endif /* !ERRORHANDLING_H_ */
