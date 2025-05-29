SOURCES = $(wildcard *.c)
BINARY = $(patsubst %.c, %, $(SOURCES))

# ******************************
CC=gcc
# ******************************

FLAGS = -W -pedantic -std=c2x -O3

# ******************************
# LIBS = -lgsl
LIBS = -lws2_32
# ******************************

.PHONY = all clean

all: $(BINARY)

$(BINARY): %: %.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)
# ******************************
# 	strip $@
# ******************************

clean:
	rm -f $(BINARY)

