#pragma once

#include "global.h"

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

void read(void);
bool eat(int token);
int scan(void);
