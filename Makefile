CC = gcc
CFLAGS = -Wall
TARGET = cdisk

all: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

