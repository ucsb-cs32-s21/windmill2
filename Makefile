#CXX=clang++
CXX=g++

FLAGS = -O3 -std=c++14 

all:
	${CXX} ${FLAGS} *.cpp

clean: 
	rm -f *.o *.out *.ppm
