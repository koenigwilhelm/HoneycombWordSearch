CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=

SOURCES=main.cpp constructTrie.cpp searchForWord.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=honeycomb.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
