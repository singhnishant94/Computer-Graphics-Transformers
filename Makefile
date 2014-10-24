OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw

GLULIB = -lGLU
SOILLIB = -lSOIL

LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(GLULIB) $(SOILLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=transformer
SRCS=gl_framework.cpp transformer_part.cpp transformer.cpp callBacks.cpp part_drawings.cpp
INCLUDES=gl_framework.hpp transformer_part.hpp callBacks.hpp part_drawings.hpp



all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~


