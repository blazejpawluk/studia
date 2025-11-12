%{
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 64

int stack[MAX_SIZE];
int top = -1;

int pop() {
	top--; 
	return stack[top+1];
}
int push(int value) {
	if (top == MAX_SIZE-1) return 0;
	top++;
	stack[top] = value;
	return 1;
}
void clear() {top = -1;}
int empty()	{return top != -1;}

int power(int x, int n) {
	if (n == 0) return 1;
	if (n == 1) return x;
	return power(x*x, n/2) * (n%2 ? x : 1);
}

char* invalid_msg;
%}

DIGIT	[0-9]
NUMBER	-?{DIGIT}+
SIGN	[+\-\*\/\^%]
WHITE	[ \t]

%x EQUATION
%x INVALID

%%
^{WHITE}*{NUMBER} {
	/* rozpoczęcie wyrażenia */
	clear();
	push(atoi(yytext));
	BEGIN(EQUATION);
}

^[^{WHITE}{NUMBER}\n] {
	/* zły znak na początku wyrażenia */
	BEGIN(INVALID);

	char* code = "blad: nieznany znak w wyrazeniu \"";
	invalid_msg = malloc(strlen(code)+strlen(yytext)+2);
	strcpy(invalid_msg, code);
	strcat(invalid_msg, yytext);
	strcat(invalid_msg, "\".");
}

<EQUATION>{NUMBER} {
	if (!push(atoi(yytext))) {
		BEGIN(INVALID);
		invalid_msg = "blad: osiagnieto limit stosu.";
	}
}
<EQUATION>{SIGN} {
	if (top < 1) {
		BEGIN(INVALID);
		invalid_msg = "blad: niewystarczajaca argumentow do dzialania.";
	}
	else {
		int b = pop(), a = pop();
		printf("%d %c %d\n", a, yytext[0], b);

		switch(yytext[0]) {
			case '+': push(a+b); break;
			case '-': push(a-b); break;
			case '*': push(a*b); break;
			case '/':
				if (b == 0) {
					BEGIN(INVALID);
					invalid_msg = "blad: proba dzielenia przez 0.";
				} else push(a/b);
				break;
			case '^':
				if (b < 0) push(1/power(a, b));
				else push(power(a, b));
				break;
			case '%':
				if (b == 0) {
					BEGIN(INVALID);
					invalid_msg = "blad: proba dzielenia przez 0.";
				} else push(a%b);
				break;
		}
	}
}
<EQUATION>{WHITE} {}
<EQUATION>\n {
	if (top > 0) printf("blad: za malo argumentow.\n");
	else if (top < 0) printf("blad: za malo znakow.\n");
	else printf(" = %d\n", pop());
	BEGIN(INITIAL);
}
<EQUATION>[^{NUMBER}{SIGN}{WHITE}\n] {
	BEGIN(INVALID);

	char* code = "blad: nieznany znak w wyrazeniu \"";
	invalid_msg = malloc(strlen(code)+strlen(yytext)+2);
	strcpy(invalid_msg, code);
	strcat(invalid_msg, yytext);
	strcat(invalid_msg, "\".");
}

<INVALID>.*\n	{printf("%s\n", invalid_msg); BEGIN(INITIAL);}
%%

int main(void) {
	yylex();
	return 0;
} 