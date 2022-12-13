CPP=g++ -g

test: schedulerTest.o process.o scheduler.o
	$(CPP) -o $@ schedulerTest.o process.o scheduler.o

schedulerTest.o: schedulerTest.cpp
	$(CPP) -c $< -o $@

process.o: process.cpp process.h
	$(CPP) -c $< -o $@

scheduler.o: scheduler.cpp scheduler.h
	$(CPP) -c $< -o $@

clean:
	rm test *.o
