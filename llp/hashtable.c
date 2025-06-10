#include "hashtable.h"
#include "prime.h"

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

static void resize (hashtable *target, size_t size) {
  hashtable *temp = malloc (sizeof (hashtable));
  temp->size      = size;
  temp->count     = 0;
  temp->buckets   = calloc (temp->size, sizeof (bucket *));

  for (size_t i = 0; i < target->size; i++) {
    bucket *bucket = target->buckets[i];
    if (bucket != NULL)
      hashtable_insert (temp, bucket->key, bucket->value);
  }

  size_t temp_size = target->size;
  target->size     = temp->size;
  temp->size       = temp_size;

  bucket **temp_buckets = target->buckets;
  target->buckets       = temp->buckets;
  temp->buckets         = temp_buckets;

  hashtable_destory (temp);
}

hashtable *hashtable_new (void) {
  hashtable *this = malloc (sizeof (hashtable));
  this->size      = 53;
  this->count     = 0;
  this->buckets   = calloc (this->size, sizeof (bucket *));
  return this;
}

void hashtable_insert (hashtable *hashtable, const char *key,
                       const char *value) {
  if ((float) hashtable->count / hashtable->size > 0.7)
    resize (hashtable, prime (hashtable->size * 2));

  bucket *current = new (key, value);
  size_t  offset  = map (current->key, hashtable->size);

  while (hashtable->buckets[offset] != NULL)
    offset = (offset + 1) % hashtable->size;

  hashtable->buckets[offset] = current;
  hashtable->count++;
}

void hashtable_delete (hashtable *hashtable, const char *key) {}

char *hashtable_search (hashtable *hashtable, const char *key) {}

void hashtable_destory (hashtable *hashtable) {
  for (size_t i = 0; i < hashtable->size; i++) {
    bucket *current = hashtable->buckets[i];
    if (current != NULL)
      delete (current);
  }

  free (hashtable->buckets);
  free (hashtable);
}
