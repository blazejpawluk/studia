EX = 2

TARGET = zad$(EX)

LEX_SRC = zad$(EX).l

LEX_GEN = zad$(EX).c

CC = gcc
CFLAGS = -O2
LDFLAGS = -lfl

all: $(TARGET).exe

$(TARGET).exe: $(LEX_GEN)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(LEX_GEN): $(LEX_SRC)
	flex -o $(LEX_GEN) $(LEX_SRC)

run: $(TARGET).exe
	./$(TARGET).exe

clean:
	rm -f $(LEX_GEN) $(TARGET).exe

.PHONY: all run clean