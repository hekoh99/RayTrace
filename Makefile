NAME=RayTracer

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEW = -Lmlx -lmlx -framework OpenGL -framework Appkit

SRCS = main.cpp parse.c parse_objs.c
INCS = ./includes
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME):		$(OBJS)
				make -C ./libft
				make -C ./mlx
				cp ./libft/libft.a libft.a
				cp ./mlx/libmlx.a ./libmlx.a
				$(CC) $(OBJS) -o $(NAME) $(FRAMEW)

%.o:			%.c
				$(CC) -I $(INCS) -c $< -o $@

clean :
	make --no-print-directory clean -C ./libft
	rm -f $(OBJS)

fclean :
	make --no-print-directory fclean -C ./libft
	make clean -C ./mlx
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f libmlx.a
	rm -f libft.a

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re