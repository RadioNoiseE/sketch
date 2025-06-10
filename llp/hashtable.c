#include "hashtable.h"
#include "prime.h"

static bucket DELETED = {NULL, NULL};

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
    if (bucket != NULL && bucket != &DELETED)
      hashtable_insert (temp, bucket->key, bucket->value);
  }

  size_t temp_size = target->size;
  target->size     = temp->size;
  temp->size       = temp_size;

  bucket **temp_buckets = target->buckets;
  target->buckets       = temp->buckets;
  temp->buckets         = temp_buckets;

  hashtable_destroy (temp);
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

  size_t  offset  = map (key, hashtable->size);
  bucket *current = hashtable->buckets[offset];

  while (current != NULL && current != &DELETED) {
    if (strcmp (current->key, key) == 0) {
      free (current->value);
      current->value = strdup (value);
      return;
    }
    offset  = (offset + 1) % hashtable->size;
    current = hashtable->buckets[offset];
  }

  hashtable->buckets[offset] = new (key, value);
  hashtable->count++;
}

void hashtable_delete (hashtable *hashtable, const char *key) {
  size_t  offset  = map (key, hashtable->size);
  bucket *current = hashtable->buckets[offset];

  while (current != NULL) {
    if (current != &DELETED && strcmp (current->key, key) == 0) {
      delete (current);
      hashtable->buckets[offset] = &DELETED;
      hashtable->count--;
      return;
    }
    offset  = (offset + 1) % hashtable->size;
    current = hashtable->buckets[offset];
  }
}

char *hashtable_search (hashtable *hashtable, const char *key) {
  size_t  offset  = map (key, hashtable->size);
  bucket *current = hashtable->buckets[offset];

  while (current != NULL) {
    if (current != &DELETED && strcmp (current->key, key) == 0)
      return current->value;
    offset  = (offset + 1) % hashtable->size;
    current = hashtable->buckets[offset];
  }

  return NULL;
}

void hashtable_destroy (hashtable *hashtable) {
  for (size_t i = 0; i < hashtable->size; i++) {
    bucket *current = hashtable->buckets[i];
    if (current != NULL && current != &DELETED)
      delete (current);
  }

  free (hashtable->buckets);
  free (hashtable);
}
