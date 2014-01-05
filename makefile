CC = gcc
SOURCES = raytrace.c vectors.c
OBJECTS = $(SOURCES:.c=.o)
TESTSOURCES = AllTests.c CuTest.c testvectors.c testraytrace.c
TESTOBJECTS = $(TESTSOURCES:.c=.o)

CFLAGS = -c -Wall
LDFLAGS = -lm

test: $(OBJECTS) $(TESTOBJECTS)
	$(CC) $(OBJECTS) $(TESTOBJECTS) $(LDFLAGS) -o test
random: $(OBJECTS) randomspheres.o
	$(CC) $(OBJECTS) randomspheres.o $(LDFLAGS) -o random
.c.o:
	$(CC) $(CFLAGS) $< -o $@
