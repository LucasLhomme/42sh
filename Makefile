##
## EPITECH PROJECT, 2025
## B-CPE-200-LIL-2-1-robotfactory-lucas.lhomme
## File description:
## Makefile
##

# Colors
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
ORANGE=\033[1;33m
NC=\033[0m # No Color

# Variables
NAME = mysh
CFLAGS = -Wall -Wextra -W -Iinclude -Ilib/include -fdiagnostics-color=always
SRC =	./src/main.c\
		./src/shell/redirect/pipe.c\
		./src/shell/redirect/simple_pipe.c\
		./src/shell/redirect/semicolon.c\
		./src/shell/redirect/redirect.c\
		./src/shell/redirect/pipe_helpers.c\
		./src/shell/hand_buffer.c\
		./src/shell/shell.c\
		./src/commands/hand_command.c\
		./src/commands/execute_command.c\
		./src/commands/searching_bin.c\
		./src/commands/cd/command_cd.c\
		./src/commands/env/command_env.c\
		./src/commands/env/my_env.c\
		./src/commands/env/handle_env.c\
		./src/commands/env/setenv.c\
		./src/commands/env/unsetenv.c\
		./src/utils/cleaning_argv.c\
		./src/utils/cleaning_buffer.c\
		./src/utils/concas_command.c\
		./src/utils/free_argv.c\

OBJ = $(SRC:.c=.o)
LIBMY = libmy.a

# Temporary file to store errors and warnings
ERRORS_FILE = .make_errors_warnings

# Default target
all: $(LIBMY) $(NAME)
	@if [ -f $(ERRORS_FILE) ]; then \
		ERRORS=$$(grep -c "error:" $(ERRORS_FILE)); \
		WARNINGS=$$(grep -c "warning:" $(ERRORS_FILE)); \
		rm -f $(ERRORS_FILE); \
		if [ $$ERRORS -eq 0 ] && [ $$WARNINGS -eq 0 ]; then \
			echo "$(ORANGE)"; \
			echo "                       @@@@@@@@  @@@@@@@@"; \
			echo "                     @@@@@@@@@@  @@@@@@@@@@"; \
			echo "                   @@@@@@@@@@@    @@@@@@@@@@@"; \
			echo "                 @@@@@@@@@@@        @@@@@@@@@@@"; \
			echo "                @@@@@@@@@@            @@@@@@@@@@"; \
			echo "               @@@@@@@@@                @@@@@@@@@"; \
			echo "        @@     @@@@@@                      @@@@@@     @@"; \
			echo "        @@     @@@@@     @@@@@@@@@@@@@@     @@@@@     @@"; \
			echo "        @@@     @@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@     @@@"; \
			echo "        @@@@     @@@@@@@@@@  @@@@@@  @@@@@@@@@@     @@@@"; \
			echo "         @@@@@    @@@@@@@@@  @@@@@@  @@@@@@@@@    @@@@@"; \
			echo "           @@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@"; \
			echo "             @@@@@@@@@@@  @@@@@@@@@@@@  @@@@@@@"; \
			echo "       @@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@"; \
			echo "      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"; \
			echo "    @@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@"; \
			echo "    @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@"; \
			echo "    @  @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@  @"; \
			echo "      @@@     @@@@@@@@@@@            @@@@@@@@@@@     @@@"; \
			echo "      @@     @@@@@                      @@@@@     @@"; \
			echo "      @     @@@@@@                      @@@@@@     @"; \
			echo "$(NC)"; \
			echo "$(GREEN)Build successful!$(NC)"; \
		elif [ $$ERRORS -eq 0 ]; then \
			echo "$(BLUE)Build successful but:"; \
			echo "$(MAGENTA)$$WARNINGS warnings!$(NC)"; \
		else \
			echo "$(RED)Build Failed!!!!$(NC)"; \
			echo "$(MAGENTA)Warnings: $$WARNINGS$(NC)"; \
			echo "$(RED)Errors: $$ERRORS$(NC)"; \
		fi; \
	else \
		echo "$(GREEN)Build successful!$(NC)"; \
	fi

# Compilation of the main executable
$(NAME): $(OBJ) $(LIBMY)
	@echo "$(YELLOW)Building $@...$(NC)"
	@OUTPUT=$$(gcc $(CFLAGS) -o $@ $^ $(LIBMY) 2>&1); \
	echo "$$OUTPUT" >> $(ERRORS_FILE); \
	ERRORS=$$(echo "$$OUTPUT" | grep -c "error:"); \
	WARNINGS=$$(echo "$$OUTPUT" | grep -c "warning:"); \
	if [ $$ERRORS -ne 0 ] || [ $$WARNINGS -ne 0 ]; then \
		echo "$$OUTPUT"; \
	fi;

# Compilation of object files
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@OUTPUT=$$($(CC) $(CFLAGS) -c $< -o $@ 2>&1); \
	echo "$$OUTPUT" >> $(ERRORS_FILE); \
	ERRORS=$$(echo "$$OUTPUT" | grep -c "error:"); \
	WARNINGS=$$(echo "$$OUTPUT" | grep -c "warning:"); \
	if [ $$ERRORS -ne 0 ] || [ $$WARNINGS -ne 0 ]; then \
		echo "$$OUTPUT"; \
	fi;

# Compilation of the library
$(LIBMY):
	@echo "$(BLUE)Building library...$(NC)"
	@$(MAKE) --no-print-directory -C lib all

# Cleaning object and temporary files
clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@$(MAKE) --no-print-directory -C lib clean
	@rm -f $(OBJ)
	@rm -f $(ERRORS_FILE)

# Clean all
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBMY)

# Rebuild all
re: fclean all

# Debug mode
debug: CFLAGS += -g
debug: $(NAME)

# Rebuild on debug mode
redebug: fclean debug

# Phony targets
.PHONY: all clean fclean re debug redebug
