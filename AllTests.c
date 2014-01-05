#include <stdio.h>

#include "CuTest.h"

CuSuite* LinearAlgebraSuite();
CuSuite* RaytraceSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, LinearAlgebraSuite());
	CuSuiteAddSuite(suite, RaytraceSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
