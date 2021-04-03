OBJS = smash.o commands.o history.o

EXE = smash

CFLAGS = -std=c99 -Wall
CC = gcc


all: $(EXE)

smash: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(EXE)

debug: CFLAGS += -DDEBUG -g -Og
debug: all

valgrind: debug
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes smash

