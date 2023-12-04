CFLAGS += -I./src
CFLAGS += -std=c++11

SRC_FILES := main.cpp 
SRC_FILES +=src/nfa.cpp 
SRC_FILES +=src/dfa.cpp 
SRC_FILES +=src/infix_to_postfix.cpp
SRC_FILES +=src/input_parser.cpp 
SRC_FILES +=src/nfa_generator.cpp 
SRC_FILES +=src/operations_handler.cpp 
SRC_FILES +=src/state.cpp
SRC_FILES +=src/token.cpp
SRC_FILES +=src/utils.cpp
SRC_FILES +=src/SubsetConstruction.cpp


build:
		g++ $(SRC_FILES) -o main $(CFLAGS)

run: build
		./main


# CXX = g++
# CXXFLAGS = -std=c++11 -Wall

# SRC_DIR = .
# # Get all .cpp files in the source directory
# SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# OBJECTS = $(SOURCES:.cpp=.o)
# EXECUTABLE = main

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

# clean:
# 	rm -f $(OBJECTS) $(EXECUTABLE)
