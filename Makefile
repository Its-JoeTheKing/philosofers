CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread -g
srcs = philo/init.c philo/parsing.c philo/timing.c philo/routine.c philo/monitoring.c philo/philo.c
ob_utils = ${srcs:.c=.o}
header = philo/philo.h

name = philo

philo/%.o: philo/%.c $(header)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(name)

$(name): $(ob_utils) $(header)
	$(CC) $(CFLAGS) $(ob_utils) -o $(name)

clean:
	$(RM) $(ob_utils)

re: clean all

fclean: clean
	$(RM) $(name)