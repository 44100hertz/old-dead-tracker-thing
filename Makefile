CFLAGS=-Wall -g

default: bin/samplefile

./bin/samplefile: src/*.c src/*.h
	gcc -std=gnu99 src/*.c -lm -o bin/samplefile

clean:
	rm -rf bin/*

.PHONY: default clean
