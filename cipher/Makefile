.PHONY: all clean
CXX = g++
CXXFLAGS = -Wall -O2
LIBS = -lcryptopp
SRC = main.cpp
BIN = cipher_prog

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LIBS)

clean:
	rm -f $(BIN)
