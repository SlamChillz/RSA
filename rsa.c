#include "rsa.h"


bool square(long b);
void factorize(long digit);
void operate(char *str);

int main(int argc, char *argv[])
{
	(void)(argc);

	if (argv[1] == NULL)
	{
		fprintf(stderr, "Usage: ./rsa <file>\n");
		exit(1);
	}

	operate(argv[1]);
	exit(0);
}

void operate(char *str)
{
	FILE *file;
	char line[1024];
	long digit;

	file = fopen(str, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: could not open file:-> %s\n", str);
		exit(1);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line[strlen(line) - 1] = '\0';
		
		if (line[0] == '\0')
			continue;

		digit = atol(line);

		factorize(digit);
	}
	return;
}

void factorize(long n)
{
	long a, b;

	a = (long) ceil(sqrt((double) n));

	b = (a * a) - n;
	
	while (!square(b))
	{
		a++;
		b = (a * a) - n;
	}

	b = (long) sqrt((double) b);

	fprintf(stdout, "%lu=%lu*%lu\n", n, a + b, a - b);
}

bool square(long b)
{
	double c;

	c = sqrt((double) b);

	if (ceil(c * c) == (double) b)
		return true;
	return false;
}

