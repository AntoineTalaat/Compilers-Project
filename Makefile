CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC_DIR = .

# Get all .cpp files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)



OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
