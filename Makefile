CC = gcc
CFLAG = -Wall -Wextra -Werror
OPTION = -pthread

TARGET = philo

SRC = main.c init.c behavior.c utils.c
OBJ = $(SRC:.c=.o)

$(NAME) : all

all : $(TARGET)

$(TARGET) : $(OBJ)
	      $(CC) $(CFLAG) -o $(TARGET) $(OBJ) $(OPTION)

$(OBJ) : $(SRC)
	   $(CC) $(CFLAG) -c $(SRC) $(OPTION)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(TARGET)

re : fclean all

.PHONY : clean fclean all re
