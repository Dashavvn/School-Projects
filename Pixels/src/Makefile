CC=g++
CFLAGS=-g -c -std=c++17 -I/usr/local/include
LDFLAGS=-L/usr/local/lib
SOURCES=main.cpp Mappings.cpp Image.cpp PNG.cpp Kernels.cpp Quantization.cpp Dither.cpp JPEG.cpp Drawing.cpp Font.cpp Vec2d.cpp Triangle.cpp Stippling.cpp SVG.cpp
LIBS=-ljpeg -lpng
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pixels

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $^ -o $@
	cp $(EXECUTABLE) ../

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
	touch *
