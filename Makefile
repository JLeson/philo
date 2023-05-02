NAME					=	philo

SRCDIR					=	./src/
INCLUDEDIR				=	./include/

SRCFILES				=	philo.c				\
							init_sim.c			\
							init_forks.c		\
							init_philosophers.c	\
							sim.c				\
							philosopher.c		\
							log.c				\
							validation.c		\
							time.c				\
							utils.c				\

SRCS					=	$(addprefix $(SRCDIR), $(SRCFILES))

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
RM						=	rm -f

all:					$(NAME)

$(NAME):				$(SRCS)
							$(CC) $(CFLAGS) $(SRCS) -I $(INCLUDEDIR) -o $(NAME)

clean:
							$(RM) $(NAME)

fclean:					clean

re:						fclean all

.PHONY:					all clean fclean re
