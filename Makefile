all:
	gcc main.c  -std=c99 -o conway -g
debug:
	gdb main
