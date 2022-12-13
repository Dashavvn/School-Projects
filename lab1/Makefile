CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=lab1.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bitops

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:  
	rm -f *.o $(EXECUTABLE) 
	touch *

handin: clean
	handin cmsc201 lab1 ../lab1


