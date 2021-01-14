SRC=./src
OBJ=./obj

all: $(OBJ) winsys

# Creating folder
$(OBJ):
	mkdir -p $(OBJ)

# Dynamik linking
winsys: $(OBJ)/main.o $(OBJ)/screen.o $(OBJ)/winsys.o $(OBJ)/snake.o
	g++ -g -Wall -pedantic -std=c++11 $^ -o $@ -lncurses

# With debugging symbols
$(OBJ)/main.o: main.cpp winsys.h screen.h cpoint.h snake.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/screen.o: screen.cpp screen.h cpoint.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/winsys.o: winsys.cpp winsys.h screen.h cpoint.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/snake.o: snake.cpp winsys.h screen.h cpoint.h snake.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

.PHONY: clean

clean:
	-rm winsys.exe $(OBJ)/*.o
