
CC = gcc
CFLAGS = -Wall -g -std=c89 -pedantic-errors

TARGET = affine_cipher

all: $(TARGET)

$(TARGET): $(TARGET).c file_pack.c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c file_pack.c

clean:
	rm $(TARGET)

#test: $(TARGET).c
#	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
#	./#NAME OF YOUR PROGRAM tfile.txt packed.out
#	ls -l tfile.txt
#	ls -l packed.out

#val:
#	valgrind --leak-check=yes ./text_compression compress tfile.txt tbinary.bin
