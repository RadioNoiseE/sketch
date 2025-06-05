#include "token.h"

static token make(int type, long offset, size_t length) {
  token this;
  this.type = type;
  this.lexeme.offset = offset;
  this.lexeme.length = length;
  return this;
};

token token_num(long num, long offset, size_t length) {
  token this = make(NUM, offset, length);
  this.value.num = num;
  return this;
};

token token_real(double real, long offset, size_t length) {
  token this = make(REAL, offset, length);
  this.value.real = real;
  return this;
};

token token_id(int type, long offset, size_t length) {
  return make(type, offset, length);
};
