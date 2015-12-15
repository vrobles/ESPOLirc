FILES  = Project15.c modules/*.c include/*.h
INPUT  = Project15.c modules/*.c
CFLAGS = -Wall -g -pthread
OUTPUT = server

all:	server

server: $(FILES)
	gcc -o $(OUTPUT) $(CFLAGS) $(INPUT)

clean: 
	rm -f server

