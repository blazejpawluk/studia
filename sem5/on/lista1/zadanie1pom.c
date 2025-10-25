#include "float.h"
#include "stdio.h"

int main() {
	printf("%.7e\n", FLT_EPSILON);
	printf("%.16e\n", DBL_EPSILON);

	printf("%.7e\n", FLT_MAX);
	printf("%.16e\n", DBL_MAX);
	return 0;
}