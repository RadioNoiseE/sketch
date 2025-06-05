#include "global.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
    return EINVAL;
  }

  FILE *fin = fopen(argv[1], "r");
  if (!fin) {
    perror("Input file error");
    return errno;
  }

  FILE *fout = fopen(argv[2], "w");
  if (!fout) {
    perror("Output file error");
    return errno;
  }

  return NOERR;
}
