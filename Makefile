CC = gcc
CFLAGS = -Wall
TARGET = ramdisk

all: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

