NAME_BONUS = philo_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
FILES_BONUS = main.c establish.c ft_atoi.c time.c \
		live.c print_msgs.c death.c

all:$(NAME_BONUS) 

OBJS_BONUS = $(FILES_BONUS:.c=.o)

$(NAME_BONUS):$(OBJS_BONUS)
	$(CC) $(FILES_BONUS) $(FLAGS) -o $(NAME_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME_BONUS)

re: fclean all