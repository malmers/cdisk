CC = gcc
CFLAGS = -Wall
TARGET = cdisk
DESTDIR = /usr/local/bin

all: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

install:
	cp $(TARGET) $(DESTDIR)/$(TARGET)
