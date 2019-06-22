OBJ := src/fancy.o src/pcg.o src/alloc.o
CFLAGS := -g -O2 -std=c11 -Wall -Wextra -Werror -Iinclude
LFLAGS := -lBearLibTerminal
CCLD ?= $(CC)

default: fancy

fancy: $(OBJ)
	$(CC) -o fancy $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ) fancy
