INCLUDES =				\
	-I../src/			\
	-I../src/tetris_ai/		\
	-I../src/tetris_x/		\
	-I../src/tetris_move/		\
	-I../src/tetris_item/		\
	-I../src/tetris_x11/		\
	-I../src/tetris_wall/		\

LIB = -lX11 -lXtst -lncurses

CFLAGS = -W -Wall -g -ggdb

SRC=$(wildcard ../src/**/*.c)

all:
	gcc $(INCLUDES) $(LIB) $(CFLAGS) $(SRC) tetris_x11_setup.c -o tetris_x11_setup
	gcc $(INCLUDES) $(LIB) $(CFLAGS) $(SRC) tetris_x11_simulation.c -o tetris_x11_simulation
	gcc $(INCLUDES) $(LIB) $(CFLAGS) $(SRC) tetris_x11_keytest.c -o tetris_x11_keytest
