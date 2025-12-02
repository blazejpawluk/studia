%{
#include <stdio.h>

extern int yylex(void);
extern int yyparse(void);
void yyerror(const char *s);
%}

%code requires {
#include "calc.h"
}

%union {
	long long val;
	Result *res;
}

%type <res> expr

%token <val> NUMBER

%left '+' '-'
%left '*' '/' '%'
%right '^'
%right UMINUS UPLUS

%%

input:
	| input line {}
;

line:
	'\n' {}
	| expr '\n' {
		printf("%s\n%d\n", $1->post, $1->value);
		freeResult($1);
	}
;

expr:
	NUMBER {$$ = resultFromLiteral($1);}
	| '(' expr ')' {$$ = $2;}
	| expr '+' expr {
		Result *r = add($1, $3);
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| expr '-' expr {
		Result *r = sub($1, $3);
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| expr '*' expr {
		Result *r = mul($1, $3);
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| expr '/' expr {
		int error;
		Result *r = divide($1, $3, &error);
		if (error) {
			yyerror("dzielenie przez zero");
			r = resultFromLiteral(0);
		}
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| expr '%' expr {
		int error;
		Result *r = mod($1, $3, &error);
		if (error) {
			yyerror("dzielenie przez zero");
			r = resultFromLiteral(0);
		}
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| expr '^' expr {
		Result *r = power($1, $3);
		freeResult($1);
		freeResult($3);
		$$ = r;
	}
	| '-' expr %prec UMINUS {
		$$ = unaryMinus($2);
		freeResult($2);
	}
	| '+' expr %prec UPLUS {
		$$ = $2;
	}

%%

void yyerror(const char *s) {
	fprintf(stderr, "Blad: %s.\n", s);
}