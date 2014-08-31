COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall -Werror -std=c++0x
LINKER = g++

all : mp1

mp1 : main.o png.o rgbapixel.o
	$(LINKER) main.o png.o rgbapixel.o -lpng -o mp1

main.o : main.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

clean :
	-rm -f *.o mp1
