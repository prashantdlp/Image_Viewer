CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I./include $(shell sdl2-config --cflags) -g -O3 
LDFLAGS = $(shell sdl2-config --libs)

# Find all .cpp files
SRCS = $(wildcard *.cpp) $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -g $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean