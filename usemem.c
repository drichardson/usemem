#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char const** argv)
{
	size_t MB = 100;

	if (argc > 1)
	{
		char* end = NULL;
		errno = 0;
		long l = strtol(argv[1], &end, 0);
		if (*end)
		{
			fprintf(stderr, "Failed to memsize argument.");
			return 1;
		}
		if (errno)
		{
			fprintf(stderr, "Error parsing memsize. %s", strerror(errno));
			return 1;
		}
		MB = l;
	}

	printf("Allocating %zu MiB.\n", MB);

	size_t const MiB = 1024 * 1024;
	size_t len = MB * MiB;
	void* m = malloc(len);
	if (m == NULL)
	{
		fprintf(stderr, "Failed to allocate %zu bytes.\n", len);
		return 1;
	}

	int rc = mlock(m, len);
	if (rc != 0)
	{
		fprintf(stderr, "Failed to lock memory. %s\n", strerror(errno));
		return 1;
	}

	while(1)
	{
		sleep(99999);
	}

	return 0;
}
