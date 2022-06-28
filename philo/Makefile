NAME	= philosopher.a
APP		= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
MFILES	= $(wildcard *.c)
MOBJ	= $(MFILES:%.c=%.o)

all		: $(NAME) run

$(NAME) : $(MOBJ)
	@ar -rcs $(NAME) $(MOBJ)

run		: $(MOBJ)
	$(CC) -o $(APP) $(CFLAGS) $(NAME) -pthread
clean	:
	@rm -rf *.o
	@rm -rf ../common/*.o
	@rm -rf $(APP)
fclean	: clean
	@rm -rf $(NAME)
re : fclean all

.PHONY: all run clean fclean re