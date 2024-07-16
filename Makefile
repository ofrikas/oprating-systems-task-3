CC = g++
CFLAGS = -std=c++11 -pthread
TARGET = ex3.out
SRC = main.cpp BoundedBuffer.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
