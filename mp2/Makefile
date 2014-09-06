CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
all: testimage

testimage : testimage.o png.o rgbapixel.o image.o
	$(LD) testimage.o png.o rgbapixel.o image.o $(LDFLAGS) -o testimage
testimage.o: testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp
png.o: png.h
	$(CXX) $(CXXFLAGS) png.cpp
rgbapixel.o : rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
image.o: image.h png.h
	$(CXX) $(CXXFLAGS) image.cpp
clean: 
	rm -f *.o testimage;