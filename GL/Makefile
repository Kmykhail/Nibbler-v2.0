NAME = gl.dylib

SRC = GL_lib.cpp

FLAGS =  -std=c++11

INC = -I ~/.brew/include -I ~/.brew/SOIL/src -I ~/.brew/include/freetype2 -I ../inc/

LIBS = -L ~/.brew/lib  -lGLEW -lglfw

T_LIBS = -L ~/.brew/lib -lftgl -lfreetype

SOIL = -L ~/.brew/SOIL/lib -lSOIL

all: $(NAME)

$(NAME):
	@g++ $(FLAGS) -dynamiclib -fPIC -o $(NAME) $(SRC) $(INC) $(LIBS) $(SOIL) $(T_LIBS) -framework OpenGL -framework Appkit
	@mv $(NAME) ..
clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re: fclean all