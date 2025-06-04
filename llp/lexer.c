#include "lexer.h"

void read() { peek = getchar(); }

bool eat(int token) {
  read();
  if (peek != token)
    return false;
  peek = RELAX;
  return true;
}

int scan() {
  for (;; read()) {
    if (peek == ' ' || peek == '\t')
      continue;
    else if (peek == '\n')
      line += 1;
    else
      break;
  }

  switch (peek) {
  case '&':
    if (eat('&'))
      return AND;
    else
      return peek;
  case '|':
    if (eat('|'))
      return OR;
    else
      return peek;
  case '=':
    if (eat('='))
      return EQ;
    else
      return peek;
  case '!':
    if (eat('='))
      return NE;
    else
      return peek;
  case '<':
    if (eat('='))
      return LE;
    else
      return peek;
  case '>':
    if (eat('='))
      return GE;
    else
      return peek;
  }

  if (isdigit(peek)) {
    long figure = 0;
    do {
      figure = 10 * figure + peek - '0';
      read();
    } while (isdigit(peek));
    if (peek != '.')
      return figure;
    // TODO: struct token, rewrite
  }

  return peek;
}
