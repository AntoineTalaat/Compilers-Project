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
SRC_FILES +=src/globals.cpp
SRC_FILES +=src/SubsetConstruction.cpp
SRC_FILES +=src/lexical_analyzer.cpp
SRC_FILES +=src/syntax_parser.cpp
SRC_FILES +=src/first_follow_builder.cpp
SRC_FILES +=src/ll1_processor.cpp

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	g++ $(SRC_FILES) -o $(EXECUTABLE) $(CFLAGS)

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)