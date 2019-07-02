OBJ := src/fancy.o src/tile.o src/being.o src/pcg.o src/alloc.o src/curses_interface.o src/blt_interface.o
CFLAGS := -g -O2 -std=c11 -Wall -Wextra -Werror -Iinclude
LFLAGS := -lBearLibTerminal -lcurses
CCLD ?= $(CC)

default: fancy

fancy: $(OBJ)
	$(CC) -o fancy $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ) fancy
