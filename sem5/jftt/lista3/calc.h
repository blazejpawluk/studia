#ifndef CALC_H
#define CALC_H

#define P 1234577LL

typedef struct {
	int value;
	int isLiteral;
	char *post;
} Result;

// tworzenie i zwalnianie Result
Result *resultFromLiteral(int rawValue);
Result *resultFromResult(int value, int isLiteral, char *post);
void freeResult(Result *r);

// operacje na Result
Result *unaryMinus(Result *a);
Result *add(Result *a, Result *b);
Result *sub(Result *a, Result *b);
Result *mul(Result *a, Result *b);
Result *divide(Result *a, Result *b, int *error);
Result *mod(Result *a, Result *b, int *error);
Result *power(Result *a, Result *b);

// pomocnicze do dzialan na Result
int modNorm(int x);
int modInv(int x);
int modPow(int base, int exp);

#endif