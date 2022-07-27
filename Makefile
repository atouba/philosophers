NAME = philo/philo
CC = cc
FLAGS = -Wall -Wextra -Werror
FILES = philo/main.c philo/establish.c philo/ft_atoi.c philo/time.c \
		philo/live.c philo/print_msgs.c philo/death.c

all:$(NAME) 

$(NAME):
	$(CC) $(FILES) -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all