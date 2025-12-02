%{
#include "parser.tab.h"
#include <string.h>

void yyerror(const char *e);
%}

DIGIT [0-9]

%x COMMENT

%%

"\\"[ \t\r]*\n			{/* przejscie do nowej linii */}
\n						{return '\n';}
[ \t] 					{/* biale znaki */}
^[ \t]*"#"				{BEGIN(COMMENT);}
<COMMENT>.				{}
<COMMENT>\\[ \t\r]*\n	{}
<COMMENT>\n				{BEGIN(INITIAL);}
{DIGIT}+				{yylval.val = atoll(yytext); return NUMBER;}
"+"						{return '+';}
"-"						{return '-';}
"*"						{return '*';}
"/"						{return '/';}
"%"						{return '%';}
"^"						{return '^';}
"("						{return '(';}
")"						{return ')';}
exit					{return EXIT;}
.						{
	setCalcError("Nieznany znak.");

	int c;
	while ((c = input()) != 0 && c != '\n') {}
	if (c == '\n') return '\n';
}

%%

int yywrap(void) {return 1;}