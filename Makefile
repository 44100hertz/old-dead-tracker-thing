CFLAGS=-Wall -g

default: bin/sampleedit

./bin/sampleedit: src/common/*.c src/common/*.h src/*.c
	gcc -std=gnu99 src/common/*.c src/sampleedit.c -lm -o bin/sampleedit

clean:
	rm -rf bin/*

.PHONY: default clean
