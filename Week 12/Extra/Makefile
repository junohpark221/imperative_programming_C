# Find the OS platform using the uname command.
Linux := $(findstring Linux, $(shell uname -s))
MacOS := $(findstring Darwin, $(shell uname -s))
Windows := $(findstring NT, $(shell uname -s))

# Specify what typing 'make' on its own will compile
default: record

# For Windows, add the .exe extension
ifdef Windows

record: record.c draw.c
	clang -std=c11 -Wall -pedantic -g $@.c draw.c -lSDL2 -o $@.exe

test: record.c test.c
	clang -std=c11 -Wall -pedantic -g record.c test.c -o $@.exe

%: %.c
	clang -Dtest_$@ -std=c11 -Wall -pedantic -g $@.c -o $@.exe

# For Linux/MacOS, include the advanced debugging options
else

record: record.c
	clang -std=c11 -Wall -pedantic -g $@.c draw.c -lSDL2 -o $@ \
	    -fsanitize=undefined -fsanitize=address -fsanitize=leak

test: record.c test.c
	clang -std=c11 -Wall -pedantic -g record.c test.c -o $@ \
	    -fsanitize=undefined -fsanitize=address -fsanitize=leak

%: %.c
	clang -Dtest_$@ -std=c11 -Wall -pedantic -g $@.c -o $@ \
	    -fsanitize=undefined -fsanitize=address -fsanitize=leak

endif
