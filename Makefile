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
UTILS_DIR	=	$(SRC_DIR)/utils
SHELL_DIR	=	$(SRC_DIR)/shell
REDIR_DIR	=	$(SHELL_DIR)/redirection
ENV_DIR		=	$(SRC_DIR)/env
CMD_DIR		=	$(SRC_DIR)/command
BUILTIN_DIR	=	$(CMD_DIR)/builtin
HISTORY_DIR	=	$(BUILTIN_DIR)/history
CD_DIR		=	$(BUILTIN_DIR)/cd
ENV_BUILTIN_DIR	=	$(BUILTIN_DIR)/env
ECHO_DIR	=	$(BUILTIN_DIR)/echo
EXIT_DIR	=	$(BUILTIN_DIR)/exit
SHELL_PROG_DIR	=	$(BUILTIN_DIR)/shell_prog
INCLUDE_DIR	=	include/
LIB		=	lib/libmy.a

SRC_FILES	=	$(CD_DIR)/my_cd.c \
			$(ENV_BUILTIN_DIR)/my_env.c \
			$(EXIT_DIR)/my_exit.c \
			$(ENV_BUILTIN_DIR)/my_setenv.c \
			$(ENV_BUILTIN_DIR)/my_unsetenv.c \
			$(BUILTIN_DIR)/is_builtin.c \
			$(ENV_BUILTIN_DIR)/setenv_case.c \
			$(CMD_DIR)/execute_command.c \
			$(CMD_DIR)/parse_command.c \
			$(REDIR_DIR)/pipe_handling.c \
			$(REDIR_DIR)/redirection_handling.c \
			$(REDIR_DIR)/semicolon_handling.c \
			$(REDIR_DIR)/double_ampersand_handling.c \
			$(REDIR_DIR)/double_pipe_handling.c \
			$(REDIR_DIR)/is_redirect.c \
			$(REDIR_DIR)/backtick_handling.c \
			$(ENV_DIR)/env_array.c \
			$(ENV_DIR)/linked_list_env.c \
			$(UTILS_DIR)/print_error.c \
			$(UTILS_DIR)/get_args.c \
			$(SRC_DIR)/main.c \
			$(SHELL_DIR)/print_prompt.c \
			$(SHELL_DIR)/read_line.c \
			$(SHELL_DIR)/insert_char.c \
			$(HISTORY_DIR)/history_handling.c \
			$(HISTORY_DIR)/linked_list_history.c \
			$(HISTORY_DIR)/history_clear.c \
			$(HISTORY_DIR)/print_n_last_command.c \
			$(HISTORY_DIR)/handle_arrow_up_down.c \
			$(ECHO_DIR)/echo.c \
			$(UTILS_DIR)/write_char.c \
			$(UTILS_DIR)/remove_first_char.c \
			$(UTILS_DIR)/handle_ctr_c.c \
			$(UTILS_DIR)/execute_seg.c \
			$(UTILS_DIR)/count_node.c \
			$(UTILS_DIR)/free_word_array.c \
			$(UTILS_DIR)/is_exit_cmd.c \
			$(SHELL_PROG_DIR)/my_which.c \
			$(SHELL_PROG_DIR)/my_where.c \
			$(SHELL_DIR)/handle_ctrl.c \
			$(SHELL_DIR)/handle_ctrl_a.c \
			$(SHELL_DIR)/handle_ctrl_e.c \
			$(SHELL_DIR)/handle_ctrl_k.c \
			$(SHELL_DIR)/handle_ctrl_l.c \
			$(SHELL_DIR)/handle_ctrl_u.c \
			$(SHELL_DIR)/handle_ctrl_w.c \
			$(SHELL_DIR)/handle_arrows.c \

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
