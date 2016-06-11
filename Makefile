CFLAGS=-Wall -g

default: bin/sampleedit

./bin/sampleedit: src/common/*.c src/common/*.h src/*.c
	gcc $(CFLAGS) -std=gnu99 src/common/*.c src/sampleedit.c -lm -o bin/sampleedit

clean:
	rm -rf bin/sampleedit

.PHONY: default clean
