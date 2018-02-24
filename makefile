CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=sfarchiver

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.gch
	rm -f *.o
	rm $(BIN)
