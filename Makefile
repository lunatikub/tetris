all:
	gcc -DEMULATION -Wstrict-overflow -lcurses -W -Wall -g -ggdb tetris_x.c tetris_map.c tetris.c tetris_ia.c  -o tetris
