all:
	gcc -DEMULATION -Wstrict-overflow -lcurses -W -Wall -g -ggdb tetris_x.c tetris.c tetris_ia.c tetris_emulation.c -o tetris

perf:
	gcc -lcurses -W -Wall -g -ggdb tetris_x.c tetris.c tetris_ia.c tetris_emulation.c -o tetris
