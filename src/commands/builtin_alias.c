/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_alias.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "shell/alias.h"
#include "shell/shell.h"
#include "utils/sentinel.h"
#include "utils/cleanup.h"
#include "utils/debug_mode.h"

static
char *alias_cut_value(context_t *ctx)
{
    char *out;
    command_t *cmd = ctx->cmd;
    size_t len = 0;
    size_t offset = 0;

    for (int i = 2; i < cmd->argc; i++)
        len += strlen(cmd->argv[i]) + 1;
    out = malloc((len + 1) * sizeof (char));
    if (!out)
        return NULL;
    for (int i = 2; i < cmd->argc; i++) {
        strcat(out + offset, cmd->argv[i]);
        offset += strlen(cmd->argv[i]);
        out[offset++] = ' ';
    }
    return out;
}

static
char *alias_translate(context_t *ctx)
{
    AUTOFREE char *out = NULL;
    AUTOFREE char *value = alias_cut_value(ctx);
    command_t *cmd = ctx->cmd;
    size_t len;
    int written;

    if (!value)
        return NULL;
    len = strlen(value) + strlen(cmd->argv[1]) + 8;
    out = malloc((len + 1) * sizeof (char));
    if (!out)
        return NULL;
    written = snprintf(out, len + 1, "alias %s=%s", cmd->argv[1], value);
    if (IS_SENTINEL(written))
        return NULL;
    return strdup(out);
}

void builtin_alias(context_t *ctx)
{
    char *out;
    command_t *cmd = ctx->cmd;

    if (cmd->argc == 1)
        return alias_list_print(ctx->aliases);
    if (cmd->argc == 2)
        return;
    out = alias_translate(ctx);
    DEBUG("-> out: %s", out);
    if (out) {
        if (alias_add(ctx->aliases, out))
            return;
        free(out);
    }
    ctx->status = EXIT_FAILURE;
}
