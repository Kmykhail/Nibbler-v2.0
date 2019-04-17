NAME = Nibller

SRC = src/main.cpp src/Menu.cpp src/Game_Obj.cpp src/Logic.cpp src/Mmap.cpp src/Food.cpp src/Interface.cpp

INC = -I inc/

OBJ = $(S_SRC:.cpp=.o)

CFLAGS = -std=c++11

CC = g++

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(INC)
	cd SDL && make
	cd SFML && make
	cd GL && make
	cd Music && make

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# install: fclean
# sh install.sh
# make

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)
	cd SDL && make fclean
	cd SFML && make fclean
	cd GL && make fclean
	cd Music && make fclean

re: fclean all