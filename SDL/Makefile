
NAME = libSDL.dylib

SRC = SDL_lib.cpp TextureManager.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++11 -dynamiclib -fPIC

CC = g++ -shared

INC = -I ~/.brew/include -I ../inc/

LIBS = -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -rpath ~/.brew/lib

#LIBS = -L /Library/Frameworks/SDL2.framework  -rpath ~/.brew/lib

all: $(NAME)

$(NAME): 
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(INC) $(LIBS)
	@mv $(NAME) ..
	@echo "\033[0;32mLib SDL built\033[0m"
	
clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re: fclean all