all: main.o

main.o: bst_main.c bst.c bst.h
	gcc -g -Wall $^ -o $@

clean:
	@echo "cleaning project"
	-rm main.o
	@echo "clean completed"

.PHONY: clean
