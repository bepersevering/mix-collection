all: main

main: linkedlist_main.o linkedlist.o 
	gcc -g -Wall $^ -o $@
linkedlist_main.o: linkedlist.h
linkedlist.o: linkedlist.h

clean:
	@echo "cleaning project"
	-rm main *.o
	@echo "clean completed"

.PHONY: clean
