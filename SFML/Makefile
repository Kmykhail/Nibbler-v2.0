
NAME = libSFML.dylib

SRC = SFML_lib.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++11 -dynamiclib -fPIC

CC = g++

INC = -I ~/.brew/include -I ../inc/

LIBS = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -rpath ~/.brew/lib

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(INC) $(LIBS)
	@mv $(NAME) ..
	@echo "\033[0;32mLib SFML built\033[0m"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re: fclean all