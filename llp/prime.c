#include "prime.h"

unsigned int prime (unsigned int limit) {
  if (limit <= 17 || limit == UINT_MAX)
    return 0;

  size_t bound  = limit / log (limit) * 1.25506;
  size_t offset = 0;

  bool         *composite = calloc (limit + 1, sizeof (bool));
  unsigned int *prime     = malloc ((bound + 1) * sizeof (unsigned int));

  for (size_t i = 2; i <= limit && offset < bound; i++) {
    if (!composite[i])
      prime[offset++] = i;
    for (size_t j = 0; j < offset; j++) {
      unsigned int current = prime[j];
      if (i * current > limit)
        break;
      composite[i * current] = true;
      if (i % current == 0)
        break;
    }
  }

  unsigned int result = prime[offset - 1];

  free (composite);
  free (prime);

  return result;
}
