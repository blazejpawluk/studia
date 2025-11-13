%{
#include <stdio.h>
%}

%x DOC

%%
^[ \t]*\"\"\"			{BEGIN(DOC);}
<DOC>[\"]{0,2}			{}
<DOC>[^\"]				{}
<DOC>\"\"\"[ \t\r]*\n	{BEGIN(INITIAL);}

\".*\"			{ECHO;}
^[ \t]*#.*\n	{}
[ \t]*#.*		{}
%%

int main(void) {
	yylex();
	return 0;
}