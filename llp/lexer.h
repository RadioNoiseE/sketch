#pragma once

#include "common.h"
#include "token.h"

#define RELAX ' '

extern int  peek;
extern long line;

token lexer_scan (FILE *stream);
