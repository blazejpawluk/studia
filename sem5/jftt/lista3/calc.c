#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int modNorm(int x) {
	int m = x % P;
	if (m < 0) m += P;
	return m;
}

int modInv(int a) {
	a = modNorm(a);

	int u = 1, w = a, x = 0, z = P;
	while (w != 0) {
		if (w < z) {
			int temp = u;
			u = x;
			x = temp;

			temp = w;
			w = z;
			z = temp;
		}

		int q = w / z;
		u -= (q*x);
		w -= (q*z);
	}

	if (z != 1) return -1;

	return modNorm(x);
}

int modPow(int base, int exp) {
	base = modNorm(base);
	exp = modNorm(exp);
	if (exp == 0) return 1;
	if (exp == 1) return base;
	return modNorm(modPow(base*base, exp/2) * (exp % 2 ? base : 1));
}

char *convertIntToString(int x) {
	char *s = (char*)malloc((int)((ceil(log10(x)) + 1) * sizeof(char)));
	sprintf(s, "%d", x);
	return s;
}

Result *resultFromLiteral(int rawValue) {
	int v = modNorm(rawValue);
	
	Result *r = (Result*)malloc(sizeof(Result));
	r->value = v;
	r->isLiteral = 1;
	r->post = convertIntToString(v);
	return r;
}

Result *resultFromResult(int value, int isLiteral, char* post) {
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

Result* unaryMinus(Result* a) {
	Result *r = resultFromLiteral(modNorm(-a->value));
	if (a->isLiteral) r->post = convertIntToString(r->value);
	else r->post = concat(a->post, " NEG");
	return r;
}

char *joinResults(const char *a, const char *b, const char* sign) {
	int lenA = strlen(a), lenB = strlen(b), lenS = strlen(sign);
	char *r = (char*)malloc(lenA+lenB+lenS+3);
	r[0] = '\0';
	r = concat(a, " ");
	r = concat(a, b);
	r = concat(a, " ");
	r = concat(a, sign);
	return r;
}

Result *add(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value + b->value),
		0,
		joinResults(a->post, b->post, "+")
	);
	return r;
}

Result *sub(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value - b->value),
		0,
		joinResults(a->post, b->post, "-")
	);
	return r;
}

Result *mul(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(a->value * b->value),
		0,
		joinResults(a->post, b->post, "*")
	);
	return r;
}

Result *divide(Result *a, Result *b, int *error) {
	int inv = modInv(b->value);
	if (!b->value || !inv) {*error = 1; return NULL;}

	Result *r = resultFromResult(
		modNorm(a->value / b->value),
		0,
		joinResults(a->post, b->post, "/")
	);
	error = 0;
	return r;
}

Result *mod(Result *a, Result *b, int *error) {
	if (!b->value) {*error = 1; return NULL;}

	Result *r = resultFromResult(
		modNorm(a->value / b->value),
		0,
		joinResults(a->post, b->post, "/")
	);
	error = 0;
	return r;
}

Result *power(Result *a, Result *b) {
	Result *r = resultFromResult(
		modNorm(modPow(a->value, b->value)),
		0,
		joinResults(a->post, b->post, "^")
	);
	return r;
}