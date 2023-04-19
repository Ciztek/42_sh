##
## EPITECH PROJECT, 2023
## Minishell
## File description:
## Makefile
##

START_TIME := $(shell date +%s%3N)

# ↓ Remove builtin rules
.SUFFIXES:

# ↓ Config
CC := gcc
NAME = 42sh

CFLAGS := -W -Wall -Wextra
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote ./include

ifeq ($(FORCE_DEBUG),1)
    CFLAGS += -D DEBUG_MODE
endif

BUILD_DIR := .build
NAME_DEBUG := debug_$(NAME)

# ↓ Clear all possible junk
SRC :=
VPATH :=

# ↓ Sources
VPATH += src
SRC += main.c

VPATH += src/core
SRC += builtins.c
SRC += command.c
SRC += environment.c
SRC += shell.c

VPATH += src/core/builtins
SRC += builtin_cd.c
SRC += builtin_env.c
SRC += builtin_exit.c
SRC += builtin_setenv.c
SRC += builtin_unsetenv.c

VPATH += src/list
SRC += list_append.c
SRC += list_create.c
SRC += list_destroy.c
SRC += list_get.c
SRC += list_remove.c

VPATH += src/utils
SRC += get_line.c
SRC += parameters.c
SRC += path.c
SRC += status.c

vpath %.c $(VPATH)

# ↓ `touch .fast` to force multi-threading
ifneq ($(shell find . -name ".fast"),)
    MAKEFLAGS += -j
endif

# ↓ Quiet
V ?=
ifeq ($(V), 1)
    $(info Verbose mode enabled)
    Q :=
else
    Q := @
endif

# ↓ Generators
OBJ := $(SRC:%.c=$(BUILD_DIR)/release/%.o)
DEBUG_OBJ := $(SRC:%.c=$(BUILD_DIR)/debug/%.o)

# ↓ Utils
ifneq ($(shell tput colors),0)
    C_RESET := \033[00m
    C_BOLD := \e[1m
    C_RED := \e[31m
    C_GREEN := \e[32m
    C_YELLOW := \e[33m
    C_BLUE := \e[34m
    C_PURPLE := \e[35m
    C_CYAN := \e[36m
endif

_SOLVE_COLORS = $(subst :r,$(C_RED), \
    $(subst :c,$(C_CYAN),            \
    $(subst :p,$(C_PURPLE),          \
    $(subst :y,$(C_YELLOW),          \
    $(subst :b,$(C_BLUE),            \
    $(subst :g,$(C_GREEN),           \
    $(subst *,$(C_BOLD),             \
    $(subst ~,$(C_RESET),            \
    $(addprefix $(call _UNQUOTE,$(1)),~)))))))))

_UNQUOTE = $(subst ",,$(subst ',,$(1)))##") ## <- Hack to make highlighter happy
_QUOTE = "$(strip $(1))"

COLORIZE = $(call _QUOTE, $(call _SOLVE_COLORS, $(1)))

CURRENT_TIME_MS = $(shell date +%s%3N)
TIME = $(shell expr $(call CURRENT_TIME_MS) - $(START_TIME))

HEADER := ":p"
LOG = @ echo -e $(call COLORIZE,$(2) ~$(TIME_BOX) $(HEADER)~ $(1)~)
TIME_BOX = "[ :b"$(call TIME)"~\t]"

# ↓ Rules
all: $(NAME)

.PHONY: all

$(NAME): $(OBJ)
	$Q $(CC) $(CFLAGS) $(LIBFLAGS) $(LDLIBS) -o $@ $^
	$(call LOG,":g$@")

$(BUILD_DIR)/release/%.o: HEADER += "release"
$(BUILD_DIR)/release/%.o: %.c
	@ mkdir -p $(dir $@)
	$Q $(CC) $(CFLAGS) -c $< -o $@
	$(call LOG, ":c" $(notdir $@))

debug: CFLAGS += -g3 -D DEBUG_MODE
debug: HEADER += "debug"
debug: $(NAME_DEBUG)

.PHONY: debug

$(NAME_DEBUG): $(DEBUG_OBJ)
	$Q $(CC) $(CFLAGS) $(LIBFLAGS) $(LDLIBS) -o $@ $^
	$(call LOG,":g$@")

$(BUILD_DIR)/debug/%.o: %.c
	@ mkdir -p $(dir $@)
	$Q $(CC) $(CFLAGS) -c $< -o $@
	$(call LOG, ":c" $(notdir $@))

clean:
	$(eval REMOVED =                                           \
		$(shell                                                \
			$(RM) -v $(OBJ) $(DEBUG_OBJ)                       \
			| grep "removed" | cut -d ' ' -f 2))
	$(call LOG,                                                \
		$(if $(REMOVED), "removed:c" $(REMOVED), "no file removed."))

fclean:
	$(call LOG,                                                \
		$(if $(shell find . -type d -name $(BUILD_DIR)),       \
			":r-:c $(BUILD_DIR)~",                             \
			"no build dir to remove."))
	@ $(RM) -r $(BUILD_DIR)
	$(eval REMOVED =                                           \
		$(shell $(RM) -v $(NAME) $(NAME_DEBUG)                 \
			| grep "removed" | cut -d ' ' -f 2))
	$(call LOG,                                                \
		$(if $(REMOVED),"removed:g" $(REMOVED), "no binary to remove."))

.PHONY: clean fclean

both: all debug

re: fclean
	+ $Q $(call RECURSE, both)

.PHONY: re both

# ↓ Utils
RECURSE = $(MAKE) $(1) --no-print-directory START_TIME=$(START_TIME)

# ↓ file & rules guard
SENTINEL = $(error Missing $(if $(findstring .,$(1)),file,rule) $(1))

%:
	$(call SENTINEL, $@)

undefine %.c

%.c:
	$(call SENTINEL, $@)