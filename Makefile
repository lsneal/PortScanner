NAME = scan

SRC = main.c \
	  InitAndDelete.c \
	  Parsing.c \
	  Scanner.c \
	  Request.c \



CFLAGS = -Wall -Wextra -Werror -pthread -g

all : $(NAME)
	
$(NAME): 
	gcc $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(SRC:.c=.o)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re bonus