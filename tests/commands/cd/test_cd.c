/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_cd.c
*/

#include "sputnik.h"
#include "run_shell_command.h"

TEST_STD(run_shell_command, cd)
$ {
    CR_ASSERT_EQ(run_shell_command("cd src"), 0);
    CR_ASSERT_STDOUT_EQ_STR("");
}