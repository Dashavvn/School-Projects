CFLAGS=-g
all: Warmup Main

Warmup: warmup.cpp
	g++ warmup.cpp boat.cpp car.cpp ${CFLAGS} -o Warmup

Main: main.cpp
	g++ main.cpp ${CFLAGS} -o Main

.PHONY: clean
clean:
	rm Warmup Main
