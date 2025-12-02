%{
#include <stdio.h>
#include <stdlib.h>

extern int calcError;

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
%type <res> expo

%token <val> NUMBER
%token EXIT

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
		if (!calcError) {
			printf("%s\nWynik: %d\n", $1->post, $1->value);
			freeResult($1);
		}
		calcError = 0;
	}
	| EXIT '\n' {exit(0);}
	| error '\n' {
		setCalcError("Niepoprawna skladnia");
		calcError = 0;
	}
	;
	
expr:
	NUMBER {
		if (calcError) $$ = makeError();
		else $$ = resultFromLiteral($1, P);
	}
	| '(' expr ')' {
		if (calcError) $$ = makeError();
		else $$ = $2;
	}
	| expr '+' expr {
		if (calcError) $$ = makeError();
		else {
			Result *r = add($1, $3);
			freeResult($1);
			freeResult($3);
			$$ = r;
		}
	}
	| expr '-' expr {
		if (calcError) $$ = makeError();
		else {
			Result *r = sub($1, $3);
			freeResult($1);
			freeResult($3);
			$$ = r;
		}
	}
	| expr '*' expr {
		if (calcError) $$ = makeError();
		else {
			Result *r = mul($1, $3);
			freeResult($1);
			freeResult($3);
			$$ = r;
		}
	}
	| expr '/' expr {
		if (calcError) $$ = makeError();
		else {
			Result *r = divide($1, $3);
			if (calcError) $$ = makeError();
			else {
				freeResult($1);
				freeResult($3);
				$$ = r;
			}
		}
	}
	| expr '%' expr {
		if (calcError) $$ = makeError();
		else {
			Result *r = mod($1, $3);
			if (calcError) $$ = makeError();
			else {
				freeResult($1);
				freeResult($3);
				$$ = r;
			}
		}
	}
	| expr '^' expo {
		if (calcError) $$ = makeError();
		else {
			Result *r = power($1, $3);
			freeResult($1);
			freeResult($3);
			$$ = r;
		}
	}
	| '-' expr %prec UMINUS {
		if (calcError) $$ = makeError();
		else {
			$$ = unaryMinus($2, P);
			freeResult($2);
		}
	}
	| '+' expr %prec UPLUS {
		if (calcError) $$ = makeError();
		else $$ = $2;
	}

expo:
	NUMBER {
		if (calcError) $$ = makeError();
		else $$ = resultFromLiteral($1, P-1);
	}
	| '(' expo ')' {
		if (calcError) $$ = makeError();
		else $$ = $2;
	}
	| '-' expo %prec UMINUS {
		if (calcError) $$ = makeError();
		else {
			$$ = unaryMinus($2, P-1);
			freeResult($2);
		}
	}
	| '+' expo %prec UPLUS {
		if (calcError) $$ = makeError();
		else $$ = $2;
	}

%%

void yyerror(const char *s) {}