/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_str_count_tok.c
*/

#include "base.h"
#include "coding_style_fix.h"
#include "sputnik.h"

#include "mocks/malloc.h"
#include "utils/sentinel.h"

TEST(str_count_tok, this_is_fine_space)
$ {
    CR_ASSERT_EQ(str_count_tok("this is fine", " "), 3);
}

TEST(str_count_tok, hello_world_l)
$ {
    CR_ASSERT_EQ(str_count_tok("Hello world", "l"), 3);
}

TEST(str_count_tok, not_in_string)
$ {
    CR_ASSERT_EQ(str_count_tok("Hello world", "x"), 1);
}

TEST(str_count_tok, longer_text)
$ {
    int ret = str_count_tok(
        "I'd just like to interject for a moment. What you're referring to as"
        " Linux, is in fact, GNU/Linux, or as I've recently taken to calling"
        " it, GNU plus Linux. Linux is not an operating system unto itself, but"
        " rather another free component of a fully functioning GNU system made"
        " useful by the GNU corelibs, shell utilities and vital system"
        " components comprising a full OS as defined by POSIX.\n"
        "Many computer users run a modified version of the GNU system every"
        " day, without realizing it. Through a peculiar turn of events, the"
        " version of GNU which is widely used today is often called Linux, and"
        " many of its users are not aware that it is basically the GNU system,"
        " developed by the GNU Project.\n"
        "There really is a Linux, and these people are using it, but it is just"
        " a part of the system they use. Linux is the kernel: the program in"
        " the system that allocates the machine's resources to the other"
        " programs that you run. The kernel is an essential part of an"
        " operating system, but useless by itself; it can only function in the"
        " context of a complete operating system. Linux is normally used in"
        " combination with the GNU operating system: the whole system is"
        " basically GNU with Linux added, or GNU/Linux. All the so-called Linux"
        " distributions are really distributions of GNU/Linux!", " "
    );

    CR_ASSERT_EQ(ret, 222);
}
