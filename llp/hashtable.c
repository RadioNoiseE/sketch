#include "hashtable.h"

static unsigned int map (const char *string, size_t size) {
  unsigned int hash = 0;
  while (*string)
    hash = hash * 131 + *string++;
  return hash % size;
}

static bucket *new (const char *key, const char *value) {
  bucket *this = malloc (sizeof (bucket));
  this->key    = strdup (key);
  this->value  = strdup (value);
  return this;
}

static void delete (bucket *bucket) {
  free (bucket->key);
  free (bucket->value);
  free (bucket);
}

hashtable *hashtable_new (void) {
  hashtable *this = malloc (sizeof (hashtable));
  this->size      = 53; // fix: prime sequence
  this->count     = 0;
  this->buckets   = calloc (this->size, sizeof (bucket *));
  return this;
}

void hashtable_insert (hashtable *hashtable, const char *key,
                       const char *value) {
  bucket *current = new (key, value);
  size_t  offset  = map (current->key, hashtable->size);
  while (hashtable->buckets[offset] != NULL) {
    offset++;
    // TODO: handle resize
  }
}

void hashtable_delete (hashtable *hashtable, const char *key) {}

char *hashtable_search (hashtable *hashtable, const char *key) {}

void hashtable_destory (hashtable *hashtable) {
  for (size_t i = 0; i < hashtable->size; i++) {
    bucket *current = hashtable->buckets[i];
    if (current != NULL)
      delete (current);
    free (hashtable->buckets);
    free (hashtable);
  }
}
