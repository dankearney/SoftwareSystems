CC=gcc
CFLAGS=-Wall $(shell pkg-config --cflags glib-2.0) -g
LIBS=$(shell pkg-config --libs glib-2.0)

glibhelloworld: hw.o
	$(CC) -o hw.o hw.c $(CFLAGS) $(LIBS)