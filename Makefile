##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## make qui file
##

RED     = \033[1;31m

GREEN   = \033[1;32m

YELLOW  = \033[1;33m

BLUE    = \033[1;34m

PINK    = \033[1;35m

ORANGE  = \033[38;5;214m

RESET   = \033[0m

NAME	=	42sh

LIBDIR	=	./lib/my

SRC_DIR		=	src

BUILTIN_DIR	=	src/builtin

COMMAND_DIR	=	src/command

ENV_DIR		=	src/env

INCLUDE_DIR	=	include/

LIB			=	lib/libmy.a

SRC_FILES	=	$(BUILTIN_DIR)/my_cd.c \
				$(BUILTIN_DIR)/my_env.c \
				$(BUILTIN_DIR)/my_exit.c \
				$(BUILTIN_DIR)/my_setenv.c \
				$(BUILTIN_DIR)/my_unsetenv.c \
				$(BUILTIN_DIR)/is_builtin.c \
				$(BUILTIN_DIR)/setenv_case.c \
				$(COMMAND_DIR)/execute_command.c \
				$(COMMAND_DIR)/parse_command.c \
				$(COMMAND_DIR)/pipe_handling.c \
				$(COMMAND_DIR)/redirection_handling.c \
				$(COMMAND_DIR)/semicolumn_handling.c \
				$(COMMAND_DIR)/is_redirect.c \
				$(ENV_DIR)/env_array.c \
				$(ENV_DIR)/linked_list_env.c \
				$(SRC_DIR)/error_handling.c \
				$(SRC_DIR)/get_args.c \
				$(SRC_DIR)/main.c

OBJ		=	$(SRC_FILES:.c=.o)

CFLAGS	+=	-g -I$(INCLUDE_DIR) -Wall -Wextra -L lib -lm

all: $(LIB) $(NAME)
	@echo -e "$(PINK)Compilation terminée !$(RESET)"

$(LIB):
	@echo -e "$(ORANGE)Compilation de la bibliothèque...$(RESET)"
	@make -C lib/my

$(NAME): $(OBJ) $(LIB)
	@echo -e "$(GREEN)Compilation de $(NAME)...$(RESET)"
	gcc -o $(NAME) $(OBJ) -Llib -lmy $(CFLAGS)
	@echo -e "$(PINK)$(NAME) compilé avec succès !$(RESET)"

%.o: %.c
	@echo -e "$(ORANGE)Compilation de $<$(RESET)"
	@gcc -c $< -o $@ $(CFLAGS)

clean:
	@echo -e "$(RED)Nettoyage des fichiers objets...$(RESET)"
	@$(MAKE) -C $(LIBDIR) clean
	@rm -f $(OBJ)

fclean: clean
	@echo -e "$(RED)Nettoyage complet...$(RESET)"
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -f $(NAME)

re: fclean all
