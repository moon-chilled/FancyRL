OBJ := src/fancy.o
CFLAGS := -g -O2 -std=c11 -Wall -Wextra -Werror
LFLAGS := -lBearLibTerminal
CCLD ?= $(CC)

default: fancy

fancy: $(OBJ)
	$(CC) -o fancy $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ) fancy
