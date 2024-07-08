TARGET  = set
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
LIBS =


CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJECTS)

mem : $(TARGET)
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)	

clean:
	rm -f $(TARGET) $(OBJECTS)