# Written 8/27/2023 #
CFLAGS=alphabeta.c -Wall -g

all:
	gcc $(CFLAGS) chess.c -o alphabeta-chess
	i686-w64-mingw32-gcc $(CFLAGS) chess.c -o alphabeta-chess
	#gcc $(CFLAGS) checkers.c -o alphabeta-checkers
