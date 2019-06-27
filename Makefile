CC = gcc
SRC = $(wildcard src/backend/*.c src/frontend/*.c)
OBJ = $(SRC:.c=.o)
BIN = ms

%.o: %.c
	$(CC) -c $< -o $@ -lncurses

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lncurses

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)

