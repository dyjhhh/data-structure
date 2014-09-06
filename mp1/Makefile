CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : mp1

mp1 : main.o png.o rgbapixel.o
	$(LD) main.o png.o rgbapixel.o $(LDFLAGS) -o mp1

main.o : main.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
clean :
	-rm -f *.o mp1