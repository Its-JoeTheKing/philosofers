CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
srcs = init.c parsing.c timing.c routine.c monitoring.c philo.c
ob_utils = ${srcs:.c=.o}
header = philo.h

name = philo

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