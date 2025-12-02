CC = gcc
FLEX = flex
BISON = bison

TARGET = calc

all: $(TARGET)

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

$(TARGET): parser.tab.c lex.yy.c calc.c main.c calc.h
	$(CC) -O2 -o $(TARGET) parser.tab.c lex.yy.c calc.c main.c
clean: 
	rm -f calc.exe lex.yy.c parser.tab.c parser.tab.h