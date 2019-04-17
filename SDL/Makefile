
NAME = libSDL.dylib

SRC = SDL_lib.cpp TextureManager.cpp

FLAGS = -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): 
	@g++ $(FLAGS) -dynamiclib -fPIC -o $(NAME) $(SRC) -I ~/.brew/include -I ../inc/ -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -rpath ~/.brew/lib
	mv $(NAME) ..
	
clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re: fclean all