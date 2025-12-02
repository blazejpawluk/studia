#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int calcError = 0;
void setCalcError(const char *msg) {
	calcError = 1;
	fprintf(stderr, "Blad: %s\n", msg);
}

long long modNorm(long long x, long long p) {
	long long m = x % p;
	if (m < 0) m += p;
	return m;
}

long long modInv(long long a) {
	a = modNorm(a, P);

	long long u = 1, w = a, x = 0, z = P;
	while (w != 0) {
		if (w < z) {
			long long temp = u;
			u = x;
			x = temp;

			temp = w;
			w = z;
			z = temp;
		}

		long long q = w / z;
		u -= (q*x);
		w -= (q*z);
	}

	if (z != 1) return -1;

	return modNorm(x, P);
}

long long modPow(long long base, long long exp) {
	base = modNorm(base, P);
	exp = modNorm(exp, P-1);
	if (exp == 0) return 1;
	if (exp == 1) return base;
	return modNorm(modPow(base*base, exp/2) * (exp % 2 ? base : 1), P);
}

char *convertIntToString(long long x) {
	if (!x) {
		char *s = (char*)malloc(sizeof(char));
		sprintf(s, "0");
		return s;
	}
	char *s = (char*)malloc((int)((ceil(log10(x)) + 1) * sizeof(char)));
	sprintf(s, "%d", x);
	return s;
}

Result *resultFromLiteral(long long rawValue, long long p) {
	long long v = modNorm(rawValue, p);

	Result *r = (Result*)malloc(sizeof(Result));
	r->value = v;
	r->isLiteral = 1;
	r->post = convertIntToString(v);
	return r;
}

Result *resultFromResult(long long value, int isLiteral, char* post) {
	Result *r = (Result*)malloc(sizeof(Result));
	r->value = value;
	r->isLiteral = isLiteral;
	r->post = post;
	return r;
}

void freeResult(Result *r) {
	if (!r) return;
	if (r->post) free(r->post);
	free(r);
}

char *concat(const char *a, const char *b) {
	int strA = strlen(a), strB = strlen(b);
	char *r = (char*)malloc(strA+strB+1);
	r[0] = '\0';
	strcat(r,a);
	strcat(r,b);
	return r;
}

Result *makeError() {
	Result *r = (Result*)malloc(sizeof(Result));
	r->value = -1;
	r->isLiteral = 1;
	r->post = concat("-", convertIntToString(1));
	return r;
}

Result* unaryMinus(Result* a, long long p) {
	Result *r = resultFromLiteral(modNorm(p-a->value, p), p);
	if (a->isLiteral) r->post = convertIntToString(r->value);
	else r->post = concat(a->post, " NEG");
	return r;
}

char *joinResults(const char *a, const char *b, const char* sign) {
	int lenA = strlen(a), lenB = strlen(b), lenS = strlen(sign);
	char *r = (char*)malloc(lenA+lenB+lenS+3);
	r[0] = '\0';
	r = concat(a, " ");
	r = concat(r, b);
	r = concat(r, " ");
	r = concat(r, sign);
	return r;
}

Result *add(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value + b->value, P),
		0,
		joinResults(a->post, b->post, "+")
	);
	return r;
}

Result *sub(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value - b->value, P),
		0,
		joinResults(a->post, b->post, "-")
	);
	return r;
}

Result *mul(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value * b->value, P),
		0,
		joinResults(a->post, b->post, "*")
	);
	return r;
}

Result *divide(Result *a, Result *b) {
	long long inv = modInv(b->value);
	if (!b->value || !inv) {
		setCalcError("Dzielenie przez 0"); 
		return NULL;
	}

	Result *r = resultFromResult(
		modNorm(a->value * inv, P),
		0,
		joinResults(a->post, b->post, "/")
	);
	return r;
}

Result *mod(Result *a, Result *b) {
	if (!b->value) {
		setCalcError("Dzielenie przez 0");
		return NULL;
	}

	Result *r = resultFromResult(
		modNorm(a->value % b->value, P),
		0,
		joinResults(a->post, b->post, "/")
	);
	return r;
}

Result *power(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(modPow(a->value, b->value), P),
		0,
		joinResults(a->post, b->post, "^")
	);
	return r;
}