CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread -g
srcs = utils/init.c utils/parsing.c utils/timing.c philo.c utils/routine.c utils/monitoring.c
ob_utils = ${srcs:.c=.o}
header = philo.h

name = philo

utils/%.o: utils/%.c $(header)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(header)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(name)

$(name): $(ob_utils) $(header)
	$(CC) $(CFLAGS) $(ob_utils) -o $(name)

clean:
	$(RM) $(ob_utils)

re: clean all

fclean: clean
	$(RM) $(name)