CFLAGS=-Wall -g

default: bin/samplefile

./bin/samplefile: src/*.c src/*.h
	gcc src/*.c -lm -o bin/samplefile

clean:
	rm -rf bin/samplefile

.PHONY: default clean
