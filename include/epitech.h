/*
** EPITECH PROJECT, 2023
** Lib ido
** File description:
** Character mapping
*/

#ifndef EPITECH_H
    #define EPITECH_H

    #define EXIT_MSG(msg, w, v) (w(msg) ? v : v)

    #define EXIT_KO_MSG(msg) EXIT_MSG(msg, eprintf, EXIT_KO)
    #define EXIT_OK_MSG(msg) EXIT_MSG(msg, printf, EXIT_OK)

typedef _Bool bool_t;

enum {
    TRUE = 1,
    FALSE = 0
};

enum {
    EXIT_OK = 0,
    EXIT_KO = 84
};

#endif /* !EPITECH_H */
