#pragma once

#include "common.h"

typedef struct {
  char *key;
  char *value;
} bucket;

typedef struct {
  size_t   size;
  size_t   count;
  bucket **buckets;
} hashtable;

hashtable *hashtable_new (void);
void       hashtable_insert (hashtable *hashtable, const char *key,
                             const char *value);
void       hashtable_delete (hashtable *hashtable, const char *key);
char      *hashtable_search (hashtable *hashtable, const char *key);
void       hashtable_destory (hashtable *hashtable);
