#ifndef CALC_H
#define CALC_H

#define P 1234577LL

typedef struct {
	long long value;
	int isLiteral;
	char *post;
} Result;

extern int calcError;
void setCalcError(const char *msg);
Result *makeError();

// tworzenie i zwalnianie Result
Result *resultFromLiteral(long long rawValue, long long p);
Result *resultFromResult(long long value, int isLiteral, char *post);
void freeResult(Result *r);

// operacje na Result
Result *unaryMinus(Result *a, long long p);
Result *add(Result *a, Result *b);
Result *sub(Result *a, Result *b);
Result *mul(Result *a, Result *b);
Result *divide(Result *a, Result *b);
Result *mod(Result *a, Result *b);
Result *power(Result *a, Result *b);

// pomocnicze do dzialan na Result
long long modNorm(long long x, long long p);
long long modInv(long long x);
long long modPow(long long base, long long exp);

#endif