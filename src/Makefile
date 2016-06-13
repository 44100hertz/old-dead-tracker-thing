CC=gcc
CFLAGS=-Wall -g -std=gnu99 -DDEBUG
DEPS = song.h
OBJ_WAVEEDIT = file.o read.o write.o get.o import.o waveedit.o

./bin/waveedit: $(OBJ_WAVEEDIT) $(DEPS)
	$(CC) -o ../bin/waveedit $(OBJ_WAVEEDIT) $(CFLAGS)

song.o read.o import.o waveedit.o: song.h

clean:
	rm $(OBJ_WAVEEDIT) ../bin/waveedit

.PHONY: clean
