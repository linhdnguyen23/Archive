CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -lstdc++
BIN=sfarchiver

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
INC=-I./include
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN) $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
