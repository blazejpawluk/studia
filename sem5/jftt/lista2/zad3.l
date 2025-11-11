%{
#include <stdio.h>
#include <string.h>

int leaveDoxygen = 0;
%}

%x MULTICOMMENT
%x COMMENT

%%
\".*\"					{ECHO; /* zwykłe napisy zostawiamy */}
\`.*\`					{ECHO; /* zwykłe napisy zostawiamy */}
#include[ \t]*\<.*\>	{ECHO; /* #include<> zostawiamy */}

\/\*\*\/		{}
.\/\*\*.*\*\/.	{if(!leaveDoxygen) printf("%c %c", yytext[0], yytext[strlen(yytext)-1]); else ECHO;}
.\/\*!.*\*\/.	{if(!leaveDoxygen) printf("%c %c", yytext[0], yytext[strlen(yytext)-1]); else ECHO;}
.\/\*.*\*\/.	{printf("%c %c", yytext[0], yytext[strlen(yytext)-1]);}

^[ \t]*\/\*\*	{if(!leaveDoxygen) BEGIN(MULTICOMMENT); else ECHO;}
[ \t]*\/\*\*	{if(!leaveDoxygen) {printf("\n"); BEGIN(MULTICOMMENT);} else ECHO;}

^[ \t]*\/\*!	{if(!leaveDoxygen) BEGIN(MULTICOMMENT); else ECHO;}
[ \t]*\/\*!		{if(!leaveDoxygen) {printf("\n"); BEGIN(MULTICOMMENT);} else ECHO;}

^[ \t]*\/\/\/	{if(!leaveDoxygen) BEGIN(COMMENT); else ECHO;}
[ \t]*\/\/\/	{if(!leaveDoxygen) {printf("\n"); BEGIN(COMMENT);} else ECHO;}

^[ \t]*\/\/!	{if(!leaveDoxygen) BEGIN(COMMENT); else ECHO;}
[ \t]*\/\/!		{if(!leaveDoxygen) {printf("\n"); BEGIN(COMMENT);} else ECHO;}

^[ \t]*\/\/		{BEGIN(COMMENT);}
[ \t]*\/\/		{printf("\n"); BEGIN(COMMENT);}

^[ \t]*\/\*		{BEGIN(MULTICOMMENT);}
[ \t]*\/\*		{printf("\n"); BEGIN(MULTICOMMENT);}

<MULTICOMMENT>[^*]+ 			{}
<MULTICOMMENT>\*+[^*/]			{}
<MULTICOMMENT>\*+\/[ \t\r]*\n	{BEGIN(INITIAL);}
<MULTICOMMENT>\*+\/				{BEGIN(INITIAL);}

<COMMENT>.*\\\n	{BEGIN(COMMENT);}
<COMMENT>.*\n	{BEGIN(INITIAL);}
%%

int main(int argc, char* argv[]) {
	if (argc > 1 && argv[1][0] == 'D') leaveDoxygen = 1;
	yylex();
	return 0;
}