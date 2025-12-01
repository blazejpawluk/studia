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
{DIGIT}+		{yylval.val = atoi(yytext); return NUMBER;}
"+"				{return '+';}
"-"				{return '-';}
"*"				{return '*';}
"/"				{return '/';}
"%"				{return '%';}
"^"				{return '^';}
"("				{return '(';}
")"				{return ')';}
.				{return yytext[0];}

%%

int yywrap(void) {return 1;}