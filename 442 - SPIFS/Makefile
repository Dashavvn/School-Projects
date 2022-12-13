CFLAGS=-g

all: filesys.o operations.o

filesys.o: filesys.h filesys.cpp
	g++ -c filesys.cpp ${CFLAGS}

operations.o: operations.cpp filesys.h
	g++ -c operations.cpp ${CFLAGS}

.PHONY: clean test submit 

clean: 
	rm -f *.o test 
	make -C tests clean

test: 
	make -C tests

submit:
	[ -d /home/robert/310Submit/${USER} ] || mkdir /home/robert/310Submit/${USER} 
	cp operations.cpp filesys.h filesys.cpp handle.h /home/robert/310Submit/${USER} && echo "Submission Accepted" || echo "Submission Failed"
