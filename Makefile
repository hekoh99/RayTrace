NAME=RayTracer

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEW = -Lmlx -lmlx -framework OpenGL -framework Appkit

SRCS = main.cpp
INCS = ./includes
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME):		$(OBJS)
				make -C ./mlx
				cp ./mlx/libmlx.a ./libmlx.a
				$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(FRAMEW)

%.o:			%.c
				$(CC) -I $(INCS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean :
	make clean -C ./mlx
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f libmlx.a

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re