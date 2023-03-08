CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -I /include
PROGRAMS = bin/ecosys.exe bin/tests_ecosys.exe bin/tests_ecosys2.exe

# Default target
all: $(PROGRAMS)

# Link ecosys executable
bin/ecosys.exe: build/ecosys.o build/main_ecosys.o
	$(CC) $(CFLAGS) $^ -o $@ 

# Link tests_ecosys executable
bin/tests_ecosys.exe: build/ecosys.o build/main_tests.o
	$(CC) $(CFLAGS) $^ -o $@

bin/tests_ecosys2.exe: build/ecosys.o build/main_tests2.o
	$(CC) $(CFLAGS) $^ -o $@

# Compile ecosys.c to ecosys.o
build/ecosys.o: src/ecosys.c include/ecosys.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main_ecosys.c to main_ecosys.o
build/main_ecosys.o: src/main_ecosys.c include/ecosys.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main_tests.c to main_tests.o
build/main_tests.o: tests/main_tests.c include/ecosys.h
	$(CC) $(CFLAGS) -c $< -o $@

build/main_tests2.o: tests/main_tests2.c include/ecosys.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f $(PROGRAMS) build/*.o

.PHONY: all clean
