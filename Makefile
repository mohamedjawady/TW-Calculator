CC = gcc

all: calculator.exe

calculator.exe: y.tab.o lex.yy.o calculator.c
		$(CC) y.tab.o lex.yy.o calculator.c -o calculator.exe

y.tab.o: y.tab.c
		$(CC) -c y.tab.c

lex.yy.o: lex.yy.c
		$(CC) -c lex.yy.c

y.tab.c: parser.y
		bison -y -g -d parser.y

lex.yy.c: lexer.l
		flex lexer.l

clean:
		rm -f y.tab.c y.tab.h lex.yy.c y.tab.o lex.yy.o calculator.exe

