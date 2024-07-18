CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = main.c set.c set_elem.c set_helpers.c
OBJECTS = $(SOURCES:.c=.o)
TESTFILES = $(shell ls input)
TARGET = setload

.PHONY: clean
.PHONY: all
.PHONY: testload
.PHONY: testelim
.PHONY: vtestelim
.PHONY: test
.PHONY: valgrind

all: $(TARGET)
testelim: testelim1 testelim2 testelim3 testelim4 testelim5
vtestelim: vtestelim1 vtestelim2 vtestelim3 vtestelim4 vtestelim5
testload: $(TESTFILES)

test: testload testelim
valgrind: vtestelim $(TESTFILES:.in=.val) 

testelim1: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-005.in -1
	@echo "\n\n"

testelim2: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-005.in 0
	@echo "\n\n"

testelim3: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-005.in 2
	@echo "\n\n"

testelim4: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-005.in 3
	@echo "\n\n"

testelim5: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	./$(TARGET) input/example-unsorted-005.in 2 0 3 -1
	@echo "\n\n"

vtestelim1: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/example-unsorted-005.in -1
	@echo "\n\n"

vtestelim2: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/example-unsorted-005.in 0
	@echo "\n\n"

vtestelim3: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/example-unsorted-005.in 2
	@echo "\n\n"

vtestelim4: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/example-unsorted-005.in 3
	@echo "\n\n"

vtestelim5: $(TARGET)
	@echo "\e[1;37mTesting $@...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/example-unsorted-005.in 2 0 3 -1
	@echo "\n\n"

%.in: $(TARGET)
	@echo "\e[1;37mTesting $*...\e[0m\e[0;37m\n"
	./$(TARGET) input/$*.in
	@echo "\n\n"

%.val: $(TARGET)
	@echo "\e[1;37mTesting $*...\e[0m\e[0;37m\n"
	valgrind --leak-check=full ./$(TARGET) input/$*.in
	@echo "\n\n"

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
