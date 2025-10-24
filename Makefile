CC = gcc
CFLAGS = -Wall -g
TARGET = main
SRCS = test.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm

clean:
	rm -f $(TARGET)

re: clean all
