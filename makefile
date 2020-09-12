# $ make

CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS  = -O3 -Wall -Wextra

SRC = main.cpp Boid.cpp Flock.cpp utils.cpp
OBJS = $(SRC:.cpp=.o)
EXEC = boid

all: $(EXEC) values.h
# all: run

debug: CFLAGS = -g
debug: $(EXEC)


Boid.o: Boid.cpp
	$(CC) $< -c $(CFLAGS)

Flock.o: Flock.cpp
	$(CC) $< -c  $(CFLAGS)

$(EXEC): $(OBJS)
	 $(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm -f $(OBJS) boid

