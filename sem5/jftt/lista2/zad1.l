%{
#include <stdio.h>

int lines = 0;
int words = 0;
%}

%%
^[ \t\r]*\n		{} /* usuwanie pustych linii */
[ \t\r]*\n		{printf("\n"); lines++;} /* usuwanie białych znaków na końcu linii + zliczanie linii *//* usuwanie białych znaków na końcu linii + zliczanie linii */
^[ \t]+			{} /* usuwanie białych znaków na początku linii */
[ \t]+			{printf(" ");} /* zamiana ciągów białych znaków na pojedynczą spację */
[^ \t\n]+		{printf("%s", yytext); words++;} /* zliczanie słów */
%%

int main(void) {
    yylex();

	/* ostatnia linia nie ma \n na końcu, więc trzeba ją dodać */
	printf("\n\nlines: %d", lines+1);
	printf("\nwords: %d", words);

    return 0;
}