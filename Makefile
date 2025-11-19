CXX = g++
CXXFLAGS = -Wall -pthread -std=c++11
TARGET = cse4001_sync
SRC = cse4001_sync.cpp

all: $(TARGET)

$(TARGET): $(SRC) semaphore_class.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
