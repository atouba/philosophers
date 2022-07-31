NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
FILES = main.c establish.c ft_atoi.c time.c \
		live.c print_msgs.c death.c


all:$(NAME) 

OBJS = $(FILES:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)


clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all