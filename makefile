CC=gcc
CFLAGS=-I. -lm
DEPS = lista.h
CFILES = $(wildcard *.c) 
DEL=rm

domino: $(CFILES:.o=)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

debug: CFLAGS += -DDEBUG 
debug: all

release: CFLAGS += -UDEBUG
release: all
