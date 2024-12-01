# Makefile 
# cppjaipur

PROG = cppjaipur

CC     = g++

CFLAGS = -Werror -Wall -std=c++20

IPATH  = -I.

FILES  =  main.cpp
FILES  += cards.cpp
FILES  += gameboard.cpp
FILES  += tokens.cpp
FILES  += player.cpp
FILES  += stateMachine.cpp

all:
	$(CC) $(CFLAGS) $(IPATH) $(FILES) $(LIBS) -o $(PROG)

.PHONY: clean

clean:
	@rm -vf *.o
	@rm -vf cppjaipur
