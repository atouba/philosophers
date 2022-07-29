NAME = philo/philo
NAME_BONUS = philo_bonus/philo_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
FILES = philo/main.c philo/establish.c philo/ft_atoi.c philo/time.c \
		philo/live.c philo/print_msgs.c philo/death.c

FILES_BONUS = philo_bonus/main.c philo_bonus/establish.c philo_bonus/ft_atoi.c philo_bonus/time.c \
		philo_bonus/live.c philo_bonus/print_msgs.c philo_bonus/death.c

all:$(NAME) 

OBJS = $(FILES:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)

bonus:$(NAME_BONUS)

OBJS_BONUS = $(FILES_BONUS:.c=.o)

$(NAME_BONUS):$(OBJS_BONUS)
	$(CC) $(OBJS_BONUS)  -o $(NAME_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all bonus

# // philo and philo_bonus should each contain their proper Makefile