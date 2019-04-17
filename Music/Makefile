
NAME = lib_Music.dylib

SRC = Music_lib.cpp

FLAGS = -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME):
	g++ $(FLAGS) -dynamiclib -fPIC -o $(NAME) $(SRC) -I ~/.brew/include -I ../inc/ -L ~/.brew/lib  -lsfml-audio -lsfml-network -lsfml-audio -rpath ~/.brew/lib
	mv $(NAME) ..
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all
