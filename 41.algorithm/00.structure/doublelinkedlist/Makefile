all: main.o

main.o: doublelinkedlist_main.o doublelinkedlist.o 
	gcc -g -Wall $^ -o $@
doublelinkedlist_main.o: doublelinkedlist.h
doublelinkedlist.o: doublelinkedlist.h

clean:
	@echo "cleaning project"
	-rm main *.o
	@echo "clean completed"

.PHONY: clean
