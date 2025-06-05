#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stdio.h>

static bool eat (FILE *stream, int token) {
  peek = fgetc (stream);
  if (peek != token)
    return false;
  peek = RELAX;
  return true;
}

token lexer_scan (FILE *stream) {
#define as_is token_id (peek, start, 1)

  for (;; peek = fgetc (stream)) {
    if (peek == ' ' || peek == '\t')
      continue;
    else if (peek == '\n')
      line += 1;
    else
      break;
  }

  long start = ftell (stream) - 1;

  switch (peek) {
  case '&':
    if (eat (stream, '&'))
      return token_id (AND, start, 2);
    else
      return as_is;
  case '|':
    if (eat (stream, '|'))
      return token_id (AND, start, 2);
    else
      return as_is;
  case '=':
    if (eat (stream, '='))
      return token_id (EQ, start, 2);
    else
      return as_is;
  case '!':
    if (eat (stream, '='))
      return token_id (NE, start, 2);
    else
      return as_is;
  case '<':
    if (eat (stream, '='))
      return token_id (LE, start, 2);
    else
      return as_is;
  case '>':
    if (eat (stream, '='))
      return token_id (GE, start, 2);
    else
      return as_is;
  }

  if (isdigit (peek)) {
    long integer = 0;
    do {
      integer = 10 * integer + peek - '0';
      peek    = fgetc (stream);
    } while (isdigit (peek));
    if (peek != '.')
      return token_num (integer, start, ftell (stream) - start);
    double figure = integer, digit = 10;
    for (;;) {
      peek = fgetc (stream);
      if (!isdigit (peek))
        break;
      figure += (peek - '0') / digit;
      digit  *= 10;
    }
    return token_real (figure, start, ftell (stream) - start);
  }

  return as_is; // FIX: set peek to relax
}
