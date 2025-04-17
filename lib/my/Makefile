##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## make qui file
##

SRC_DIR		=	.

LIB_DIR		=	../

SRC		=	my_putstr.c \
			my_putchar.c \
			my_strlen.c \
			my_revstr.c \
			my_compute_power_rec.c \
			my_compute_square_root.c \
			my_find_prime_sup.c \
			my_getnbr.c \
			my_isneg.c \
			my_is_prime.c \
			my_put_nbr.c \
			my_sort_int_array.c \
			my_strcat.c \
			my_strcmp.c \
			my_strcpy.c \
			my_strncat.c \
			my_strncmp.c \
			my_strncpy.c \
			my_strstr.c \
			my_swap.c \
			copy_word.c \
			count_words.c \
			is_alnum.c \
			my_str_to_word_array.c \
			fill_word_array.c \
			my_printf.c \
			handle_char.c \
			handle_str.c \
			handle_int.c \
			percent.c \
			handle_hex.c \
			handle_hexmaj.c \
			handle_oct.c \
			handle_ptr.c \
			handle_flottants.c \
			handle_e.c \
			my_put_unsigned_nbr.c \
			handle_unsigned.c \
			my_strdup.c \
			str_to_digit.c \
			fill_word_array.c \
			my_strcspn.c \
			my_atoi.c \
			my_strndup.c \
			get_env.c \
			my_remove_char.c \
			len_tab.c \
			my_strchr.c \
			is_str_alnum.c

OBJ		=	$(SRC:.c=.o)

NAME	=	libmy.a

all:			$(NAME)

$(NAME):		$(OBJ)
		ar rc -o $(NAME) $(OBJ)
		mv $(NAME) $(LIB_DIR)
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(LIB_DIR)$(NAME)

re: fclean all
