NAME = ft_ssl

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDE_DIR = ./includes

DIR_OBJ = ./obj/

DIR_LIB = ./libft/

SRC_DIR = ./srcs/

FILES = main.c \
			manage_hash.c \
			manage_hash2.c \
			md5.c \
			sha.c \
			sha224.c \
			sha256.c \
			sha384.c \
			sha512.c \
			sha512_bis.c \
			sha512t.c \
			print.c \
			utils.c \
			init_algo.c \
			add_values.c \
			manage_byte.c


SRCS = $(addprefix $(SRC_DIR), $(FILES))

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(FILES))

DEP_OBJ = src_msg \
		  $(OBJS)

RM = /bin/rm -rf

all: mkdirobj $(DEP_OBJ)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -o $(NAME) $(OBJS) -L $(DIR_LIB) -I $(INCLUDE_DIR) -lft
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ make clean -C $(DIR_LIB)
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ make fclean -C $(DIR_LIB)
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME)
	@ $(RM) $(NAME).dSYM
	@ echo " \033[32mdone\033[0m"

debug:
	@ make -C $(DIR_LIB)
	$(CC) -o $(NAME) $(SRCS) -L$(DIR_LIB) -I$(INCLUDE_DIR) -lft -g

re: fclean all

src_msg:
	@ echo " src functions:"

.PHONY : all mkdirobj clean fclean re