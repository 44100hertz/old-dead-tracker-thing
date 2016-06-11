CFLAGS=-Wall -g -std=gnu99

default: bin/sampleedit

./bin/sampleedit: src/common/*.c src/common/*.h src/*.c
	gcc $(CFLAGS)
	src/common/*.c src/pcmlib/file/*.c src/pcmlib/*.c src/sampleedit.c
	-lm -o bin/sampleedit

clean:
	rm -rf bin/sampleedit

.PHONY: default clean
