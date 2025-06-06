#include "prime.h"

void prime (unsigned int *array, unsigned int limit) {
  if (limit == UINT_MAX)
    limit -= 1;

  bool  *composite = (bool *) calloc (limit + 1, sizeof (bool));
  size_t offset    = 0;

  for (size_t i = 2; i <= limit; i++) {
    if (!composite[i])
      array[offset++] = i;
    for (size_t j = 0; j < offset; j++) {
      unsigned int prime = array[j];
      if (i * prime > limit)
        break;
      composite[i * prime] = true;
      if (i % prime == 0)
        break;
    }
  }

  free (composite);
}
