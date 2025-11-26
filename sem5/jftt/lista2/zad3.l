%{
#include <stdio.h>
#include <string.h>

int leaveDoxygen = 0;
%}

%x COMMENT
%x MULTICOMMENT

%%

\".*\" {ECHO;}
#include[ \t]*<.*> {ECHO;}

^[ \t]*\/\*[\*!][^\/] {if (leaveDoxygen) ECHO; else BEGIN(MULTICOMMENT);}
[ \t]*\/\*[\*!][^\/] {if (leaveDoxygen) ECHO; else {printf(" "); BEGIN(MULTICOMMENT);}}

^[ \t]*\/\/[\/!] {if (leaveDoxygen) ECHO; else BEGIN(COMMENT);}
[ \t]*\/\/[\/!] {if (leaveDoxygen) ECHO; else {printf("\n"); BEGIN(COMMENT);}}

^[ \t]*\/\/ {BEGIN(COMMENT);}
[ \t]*\/\/ {printf("\n"); BEGIN(COMMENT);}

^[ \t]*\/\* {BEGIN(MULTICOMMENT);}
[ \t]*\/\* {printf(" "); BEGIN(MULTICOMMENT);}

<COMMENT>\\[ \t\r]*\n {}
<COMMENT>\n {BEGIN(INITIAL);}
<COMMENT>. {}

<MULTICOMMENT>\*\/[ \t\r]* {BEGIN(INITIAL);}
<MULTICOMMENT>\*\/[ \t\r]*\n {BEGIN(INITIAL);}
<MULTICOMMENT>. {}
<MULTICOMMENT>\n {}

%%

int main(int argc, char* argv[]) {
	if (argc > 1 && argv[1][0] == 'D') leaveDoxygen = 1;
	yylex();
	return 0;
}