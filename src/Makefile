CC=gcc
CFLAGS=-Wall -g -std=gnu99
DEPS = song.h
OBJ_WAVEEDIT = file.o read.o write.o waveedit.o

./bin/waveedit: $(OBJ_WAVEEDIT) $(DEPS)
	$(CC) -o ../bin/waveedit $(OBJ_WAVEEDIT) $(CFLAGS)

song.o file.o read.o read.o: song.h

clean:
	rm $(OBJ_WAVEEDIT) ../bin/waveedit

.PHONY: clean
