#include <stdlib.h>

void *alloc(size_t size) {
	void *ret = calloc(1, size);

	if (ret == NULL) {
		abort();
	}

	return ret;
}
