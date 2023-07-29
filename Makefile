TARGET = enc
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -o $(TARGET)

SRC= encrypt.c key.c main.c
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

-include $(DEP)

main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)	

clean:
	rm -f *.o $(TARGET)
	rm -f test

test:
	./$(TARGET) "Hello World" test
	cat test