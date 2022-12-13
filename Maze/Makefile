# Lists all executable targets
all: test_Location test_Maze

# For each target, list its components (use .o for the .cpp files) and
# show how to build the target
test_Location: test_Location.u Location.o
	compile $^ -o test_Location

test_Maze: test_Maze.u Maze.o Location.o
	compile $^ -o test_Maze

# For each component, list the files it depends on, including all the .h
# files that it directly or indirectly includes
Location.o: Location.cpp Location.h
Maze.o: Maze.cpp Maze.h Location.h

# How to turn .cpp files into .o files
%.o : %.cpp
	compile -O0 -c $<

# What to run if someone types "make clean" (removes temporary files)
clean:
	rm -f *.o *.gch
