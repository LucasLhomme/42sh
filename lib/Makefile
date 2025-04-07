##
## EPITECH PROJECT, 2024
## Makefile lib
## File description:
## MakeFile dans le fichier lib
##

NAME = libmy.a

CFLAGS += -Wall -Werror -Wextra -W -Iinclude -pthread


LIB =	./check_strisnum.c\
	./my_compute_power_rec.c\
	./my_getnbr.c\
	./my_is_prime.c\
	./my_isneg.c\
	./my_put_nbr.c\
	./my_putchar.c\
	./my_putstr.c\
	./my_revstr.c\
	./my_strdup.c\
	./my_strncmp.c\
	./my_strcpy.c\
	./my_strlen.c\
	./my_strncpy.c\
	./my_swap.c\
	./my_print_comb2.c\
	./my_print_com.c\
	./my_strndup.c\
	./my_sort_params.c\
	./my_evil_str.c\
	./my_revstr.c\
	./my_str_str.c\
	./my_str_to_word_array.c\
	./my_str_to_word_array_advanced.c\
	./isalphanum.c\
	./blanck.c\
	./flag_c.c\
	./flag_d.c\
	./flag_i.c\
	./flag_o.c\
	./flag_percent.c\
	./flag_s.c\
	./flag_x.c\
	./flag_x2.c\
	./my_printf.c\
	./my_strcmp.c\
	./my_strcat.c\
	./my_uppercase.c\
	./my_isalpha.c\
	./nonalphanumeric.c\
	./my_isnum.c\
	./my_strchr.c\
	./my_strtok.c\
	./my_trimspace.c\


OBJ_LIB  	=	 $(LIB:.c=.o)


all: 	$(NAME)

$(NAME):	$(OBJ_LIB)
		ar rcs $(NAME) $(OBJ_LIB)
		mv $(NAME) ../
		make clean

clean:
		rm -f $(OBJ_LIB)

fclean:
		rm -f $(NAME) $(OBJ_LIB)

re:
		$(MAKE) fclean
		$(MAKE) all
