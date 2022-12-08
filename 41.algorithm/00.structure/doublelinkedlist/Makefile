all: main.o

main.o: doublelinkedlist_main.c doublelinkedlist.c doublelinkedlist.h
	gcc -g -Wall $^ -o $@

clean:
	@echo "cleaning project"
	-rm main.o
	@echo "clean completed"

.PHONY: clean
