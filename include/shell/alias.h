/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias.h
*/

#ifndef ALIAS_H
    #define ALIAS_H

typedef _Bool bool_t;
typedef struct list_s list_t;

typedef struct command_s command_t;
typedef struct context_s context_t;

typedef struct aliases_s {
    char *config_file;
    char **lines;
    list_t *pool;
} aliases_t;

typedef struct {
    char *key;
    size_t member_count;
    char **members;
} alias_t;

// Management
aliases_t *alias_list_create(void);
void alias_list_destroy(aliases_t *aliases);

// List
int alias_add(list_t *alias, char *input);
void alias_remove(list_t *alias, char *input);

// utils
bool_t is_alias(char *str);
bool_t alias_is_same_key(char *alias, char *input);

void alias_resolve(aliases_t *aliases, command_t *cmd);
void alias_print_command(aliases_t *aliases);

#endif
