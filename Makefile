CC		=gcc
CFLAGS	=-Wall -pedantic -Wextra -g
OBJECTS	=bin/driver.o bin/lex.yy.o
EXEC 	=jsh
LINK	=-lfl
INCLUDE	=./include


#
# This specifies which rules take no parameters.
#
.PHONY: all clean


all: build


#
# This is the normal compilation rule.  Simply typing 'make' will run this
#
build: $(OBJECTS)
	$(CC) $(CFLAGS) src/main.c -o $(EXEC) $(OBJECTS) -I$(INCLUDE) $(LINK)

#
# Object rules:
#

bin/lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o bin/lex.yy.o

lex.yy.c: src/lex.c
	flex src/lex.c

bin/driver.o: src/driver.c
	$(CC) $(CFLAGS) src/driver.c -c -o bin/driver.o -I$(INCLUDE)

#
# Clean-up rules.  Removes the executable and objects.
#

test: lex.yy.o
	gcc $(CFLAGS) src/main.c src/driver.c ./lex.yy.o -I./include $(LINK)

clean:
	rm $(EXEC) $(OBJECTS) ./lex.yy.c
