# Lists all executable targets
all: test_Card show_library_stuff

# For each target, list its components (use .o for the .cpp files) and
# show how to build the target
test_Card: test_Card.u Card.o
	compile $^ -o test_Card -lcppunit

show_library_stuff: show_library_stuff.o Card.o
	compile $^ -o show_library_stuff

# For each component, list the files it depends on, including all the .h
# files that it directly or indirectly includes
Card.o: Card.cpp Card.h
show_library_stuff.o: show_library_stuff.cpp Card.h

test_Card.o: test_Card.u Card.h
	uncic test_Card.u

# How to turn .cpp files into .o files
%.o : %.cpp
	compile -O0 -c $<

# What to run if someone types "make clean" (removes temporary files)
clean:
	rm -f *.o *.gch
