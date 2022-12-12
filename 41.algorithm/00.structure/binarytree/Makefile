all: main.o

main.o: binarytree_main.c binarytree.c binarytree.h
	gcc -g -Wall $^ -o $@

clean:
	@echo "cleaning project"
	-rm main.o
	@echo "clean completed"

.PHONY: clean
