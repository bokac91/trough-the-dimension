# Osnovni makefile
PROGRAM = pkd
CC	= gcc
CFLAGS  = -Wall -g
LIBS = -lm -lGL -lGLU -lglut

$(PROGRAM): main.o funcs.o other.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o funcs.o other.o $(LIBS)
	
.PHONY: clean fullc

clean:
	-rm -f *.o 

fullc: 
	-rm -f *.o $(PROGRAM)

	

