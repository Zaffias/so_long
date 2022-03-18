
SRCS =	so_long.c	ft_strlen.c	ft_split.c	handle_errors.c
OBJS = ${SRCS:.c=.o}

HDRS = so_long.h

NAME = so_long

cc = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -Ilmx -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework Appkit -o $(NAME)


all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
