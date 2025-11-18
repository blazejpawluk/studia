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
[^ \t\n]+		{ECHO; words++;} /* zliczanie słów */
%%

int main(void) {
    yylex();

	printf("\n\nlines: %d", lines);
	printf("\nwords: %d", words);

    return 0;
}