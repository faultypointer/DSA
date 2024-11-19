#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========= HASHMAP IMPLEMENTATION =========================================
#define u64 uint64_t
#define u32 uint32_t
typedef struct HashNode {
  char *key;
  u32 value;
  struct HashNode *next;
} HashNode;

typedef struct {
  HashNode **buckets;
  size_t size;
  size_t capacity;
  float load_factor;
} HashMap;

u32 hash(char *key, size_t cap) {
  u32 hash_value = 0;
  while (*key != '\0') {
    hash_value += *key++;
    hash_value += hash_value << 10;
    hash_value ^= hash_value >> 6;
  }
  hash_value += hash_value << 3;
  hash_value ^= hash_value >> 11;
  hash_value += hash_value << 15;
  return hash_value % cap;
}

// **************** INITIALIZATION FUNCTIONS *******************************
//
// functions to initialize HashMap
// on success returns a pointer to HashMap
// on failure returns NULL
// can fail if malloc to HashMap itself returns NULL or if
// initializing buckets field returns NULL from calloc
// should be manually freed using hm_deinit()

#define DEFAULT_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75
HashMap *hm_init_full(size_t cap, float lf) {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL) {
    return NULL;
  }
  map->capacity = cap;
  map->load_factor = lf;
  map->size = 0;
  map->buckets = (HashNode **)calloc(cap, sizeof(HashNode *));
  if (map->buckets == NULL) {
    free(map);
    return NULL;
  }
  return map;
}

HashMap *hm_init_with_capacity(size_t cap) {
  return hm_init_full(cap, DEFAULT_LOAD_FACTOR);
}

HashMap *hm_init_with_load_factor(float lf) {
  return hm_init_full(DEFAULT_CAPACITY, lf);
}

HashMap *hm_init() {
  return hm_init_full(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
}
// *************************************************************************************

// increases the capacity of map
// return 0 on success
// returns -1 if calloc using new_capacity fails
int hm_grow_capacity(HashMap *map) {
  size_t old_cap = map->capacity;
  HashNode **old_buckets = map->buckets;
  size_t new_cap = old_cap * 2;

  map->capacity = new_cap;
  map->buckets = (HashNode **)calloc(new_cap, sizeof(HashNode *));
  if (map->buckets == NULL) {
    // in case calloc fails
    // set map's buckets to point to old buckets then
    map->buckets = old_buckets;
    // return early
    return -1;
  }

  // rehash old values and put them in new bucket
  for (int i = 0; i < old_cap; i++) {
    HashNode *curr_node = old_buckets[i];
    while (curr_node != NULL) {
      HashNode *tmp_next = curr_node->next;
      u32 new_hash = hash(curr_node->key, new_cap);
      curr_node->next = map->buckets[new_hash];
      map->buckets[new_hash] = curr_node;
      curr_node = tmp_next;
    }
  }
  free(old_buckets);

  return 0;
}

// insert the key value pairs in the HashMap
// if key already exists, updates the key's value with new value
// returns pointer to the HashNode of (K, V) pair
// or NULL incase malloc fails when creating new HashNode
HashNode *hm_insert(HashMap *map, char *key, u32 val) {
  if ((float)(map->size + 1) / map->capacity > map->load_factor) {
    if (hm_grow_capacity(map) == -1) {
      printf("failed to grow capacity\n");
    }
  }

  // calculate hash
  u32 hash_val = hash(key, map->capacity);
  HashNode *curr_node = map->buckets[hash_val];
  while (curr_node != NULL) {
    // if key already exists update it's value
    if (strcmp(curr_node->key, key) == 0) {
      curr_node->value = val;
      return curr_node;
    }
    curr_node = curr_node->next;
  }

  // create node
  HashNode *node = (HashNode *)malloc(sizeof(HashNode));
  if (node == NULL)
    return NULL;
  node->value = val;
  node->key = strdup(key);
  node->next = map->buckets[hash_val];
  map->buckets[hash_val] = node;
  map->size += 1;

  return node;
}

HashNode *hm_get_node(HashMap *map, char *key) {
  u32 hash_val = hash(key, map->capacity);
  HashNode *curr_node = map->buckets[hash_val];
  while (curr_node != NULL) {
    if (strcmp(curr_node->key, key) == 0) {
      return curr_node;
    }
    curr_node = curr_node->next;
  }
  return NULL;
}

u32 hm_get_orelse(HashMap *map, char *key, u32 def) {
  HashNode *node = hm_get_node(map, key);
  if (node == NULL) {
    return def;
  }
  return node->value;
}

bool hm_contains(HashMap *map, char *key) {
  return hm_get_node(map, key) != NULL;
}

void hm_remove(HashMap *map, char *key) {
  u32 hash_val = hash(key, map->capacity);
  HashNode *curr_node = map->buckets[hash_val];
  HashNode *prev_node = NULL;
  while (curr_node != NULL) {
    if (strcmp(curr_node->key, key) == 0) {
      if (prev_node == NULL) {
        map->buckets[hash_val] = curr_node->next;
      } else {
        prev_node->next = curr_node->next;
      }
      free(curr_node->key);
      free(curr_node);
      map->size -= 1;
      return;
    }
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
}

void hm_deinit(HashMap *map) {
  for (int i = 0; i < map->capacity; i++) {
    HashNode *curr_node = map->buckets[i];
    while (curr_node != NULL) {
      HashNode *tmp_next = curr_node->next;
      free(curr_node->key);
      free(curr_node);
      curr_node = tmp_next;
    }
  }
  free(map->buckets);
  free(map);
}

// ====================================================================================

// =======================helper function definations
// ============================= prints the help message if error is true first
// prints the error message then prints the help message
void print_help(bool error, char *errmsg) {
  if (error && errmsg != NULL) {
    printf("Error: %s\n", errmsg);
  }
  printf("Usage: docdist <file1> <file2>\n");
  printf("Description: Checks the distance of two text files based on the "
         "frequencies of each word appearing in both files.\n");
}

// opens two files passed in arguments
// returns -1 incase an error occurs while opening the files
// returns 0 if successful
int read_file(FILE **fp1, FILE **fp2, char *filenames[2]) {
  *fp1 = fopen(filenames[0], "r");
  if (fp1 == NULL) {
    printf("Error opening file %s. Error: %s\n", filenames[0], strerror(errno));
    return -1;
  }

  *fp2 = fopen(filenames[1], "r");
  if (fp2 == NULL) {
    printf("Error opening file %s. Error: %s\n", filenames[1], strerror(errno));
    return -1;
  }
  return 0;
}

// Reads a file in chunks and tokenizes the text to count word frequencies,
// storing results in a hashmap.
// only ascii alphanumeric characters are considered for words
// uppercase characters are converted to lowercase characters
void vectorize(FILE *fp, HashMap *map) {
  size_t buf_len = 100000;
  char buf[buf_len];
  int byte_read = 0;
  char word_buf[100];
  int wordlen = 0;
  do {
    byte_read = fread(buf, sizeof(char), buf_len, fp);
    for (int i = 0; i < byte_read; i++) {
      char byte = buf[i];
      if ((byte >= 'a' && byte <= 'z') || (byte >= '0' && byte <= '9'))
        word_buf[wordlen++] = byte;
      else if (byte >= 'A' && byte <= 'Z')
        word_buf[wordlen++] = byte + ('a' - 'A');
      else if (wordlen > 0) {
        word_buf[wordlen] = '\0';
        HashNode *node = hm_get_node(map, word_buf);
        if (node == NULL) {
          hm_insert(map, word_buf, 1);
        } else {
          node->value += 1;
        }
        wordlen = 0;
      }
    }
  } while (byte_read == buf_len);
}

// calculates the dot product of two document vectors
uint64_t dot_product(HashMap *vec1, HashMap *vec2) {
  uint64_t result = 0;
  for (int i = 0; i < vec1->capacity; i++) {
    HashNode *node1 = vec1->buckets[i];
    while (node1 != NULL) {
      HashNode *node2 = hm_get_node(vec2, node1->key);
      if (node2 != NULL) {
        result += (uint64_t)node1->value * node2->value;
      }
      node1 = node1->next;
    }
  }
  return result;
}

uint64_t vector_length(HashMap *vec) {
  uint64_t result = 0;
  for (int i = 0; i < vec->capacity; i++) {
    HashNode *node = vec->buckets[i];
    while (node != NULL) {
      result += node->value * node->value;
      node = node->next;
    }
  }
  return result;
}

double cosine_distance(HashMap *vec1, HashMap *vec2) {
  double dot = (double)dot_product(vec1, vec2);
  double length_product =
      sqrt((double)vector_length(vec1) * vector_length(vec2));
  return acos(dot / length_product);
}

// ================================================================

int main(int argc, char *argv[]) {
  if (argc < 3) {
    print_help(true, "Too few arguments.");
    return 1;
  } else if (argc > 3) {
    print_help(true, "Too many arguments.");
    return 1;
  }
  FILE *fp1, *fp2;
  if (read_file(&fp1, &fp2, argv + 1) == -1) {
    return 1;
  }

  HashMap *vector_one = hm_init_with_capacity(512);
  HashMap *vector_two = hm_init_with_capacity(512);
  vectorize(fp1, vector_one);
  vectorize(fp2, vector_two);
  fclose(fp1);
  fclose(fp2);
  printf("[File %s]: %ld distinct words\n", argv[1], vector_one->size);
  printf("[File %s]: %ld distinct words\n", argv[2], vector_two->size);

  printf("Distance between documents: %f(radians)\n",
         cosine_distance(vector_one, vector_two));

  // free hashmaps
  hm_deinit(vector_one);
  hm_deinit(vector_two);
  return 0;
}
