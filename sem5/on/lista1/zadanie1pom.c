#include "float.h"
#include "stdio.h"

int main() {
	printf("%.7e\n", FLT_EPSILON);
	printf("%.15e\n", DBL_EPSILON);
	return 0;
}