NAME = libGL.dylib

SRC = GL_lib.cpp

CFLAGS = -std=c++11 -dynamiclib -fPIC

CC = g++

INC = -I ~/.brew/include -I ~/.brew/SOIL/src -I ~/.brew/include/freetype2 -I ../inc/

LIBS = -L ~/.brew/lib  -lGLEW -lglfw

T_LIBS = -L ~/.brew/lib -lftgl -lfreetype

SOIL = -L ~/.brew/SOIL/lib -lSOIL

all: $(NAME)

$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(INC) $(LIBS) $(SOIL) $(T_LIBS) -framework OpenGL -framework Appkit
	@mv $(NAME) ..
	@echo "\033[0;32mLib OpenGL built\033[0m"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re: fclean all