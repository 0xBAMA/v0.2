CC=g++

MAKE_EXE=-o exe

CFLAGS=-O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -std=c++11

and_go:	./includes/voraldo/V2.cc ./includes/voraldo/V2.h main.cc
	clear
	$(CC) $(MAKE_EXE) main.cc ./includes/voraldo/V2.cc $(CFLAGS)

go:
	./exe