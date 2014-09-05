EXE = mp1
OBJS = main.o png.o rgbapixel.o

COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror -std=c++0x
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) :$(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXE)
