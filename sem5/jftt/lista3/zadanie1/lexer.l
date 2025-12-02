%{
#include "parser.tab.h"
#include <string.h>

void yyerror(const char *e);
%}

DIGIT [0-9]

%%

"\\"[ \t\r]*\n	{/* przejscie do nowej linii */}
\n				{return '\n';}
[ \t] 			{/* biale znaki */}
^[ \t]*"#".*	{/* komentarz */}
{DIGIT}+		{yylval.val = atoll(yytext); return NUMBER;}
"+"				{return '+';}
"-"				{return '-';}
"*"				{return '*';}
"/"				{return '/';}
"%"				{return '%';}
"^"				{return '^';}
"("				{return '(';}
")"				{return ')';}
.				{
	setCalcError("Nieznany znak.");

	int c;
	while ((c = input()) != 0 && c != '\n') {}
	if (c == '\n') return '\n';
}

%%

int yywrap(void) {return 1;}