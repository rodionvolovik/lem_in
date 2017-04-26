NAME = lem_in
INCLUDES = -I./get_next_line -I./ -I./libft
LIBFT = libft/libft.a
OBJ = lem_in.o \
			get_next_line/get_next_line.o \
			srcs/read_map.o \
			srcs/find_roots.o

.phony: all clean fclean re

all: $(OBJ) $(LIBFT)
	@ gcc -Wall -Wextra -Werror $(LIBFT) $(OBJ) -o $(NAME)
	@ echo "\x1b[32m Project was successfully compiled \x1b[0m"

$(LIBFT):
	@ make -C ./libft
	@ echo "\x1b[32m Library was successfully compiled \x1b[0m"

%.o : ./%.c
	@ gcc -Wall -Wextra -Werror -o $@ -c $< $(INCLUDES)
	@ echo "\x1b[32m Compiling object files \x1b[0m"

clean:
	@ make clean -C ./libft
	@ /bin/rm -f $(OBJ)

fclean: clean
	@ /bin/rm -f libft/libft.a
	@ /bin/rm -f $(NAME)
	@ echo "\x1b[31m You deleted this project binaries \x1b[0m"

re: fclean all
