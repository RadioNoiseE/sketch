#pragma once

#include "common.h"

enum tag {
  AND = 256, // after 255 ascii characters
  BASIC,
  BREAK,
  DO,
  ELSE,
  EQ,
  FALSE,
  GE,
  ID,
  IF,
  INDEX,
  LE,
  MINUS,
  NE,
  NUM,
  OR,
  REAL,
  TEMP,
  TRUE,
  WHILE
};

typedef struct {
  int type;
  union {
    long   num;
    double real;
  } value;
  struct {
    long   offset;
    size_t length;
  } lexeme;
} token;

token token_num (long value, long offset, size_t length);
token token_real (double value, long offset, size_t length);
token token_id (int type, long offset, size_t length);
