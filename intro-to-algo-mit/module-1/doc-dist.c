#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// ========= HASHMAP IMPLEMENTATION =========================================
#define u64 uint64_t
#define u32 uint32_t
typedef struct {
  char *key;
  u32 value;
  struct HashNode *next;
} HashNode;

typedef struct {
  HashNode **buckets;
  size_t bucket_count;
} HashMap;

u32 hash(char *key, size_t bucket_count) {
  u32 hash_value = 0;
  while (*key != '\0') {
    hash_value += *key++;
    hash_value += hash_value << 10;
    hash_value ^= hash_value >> 6;
  }
  hash_value += hash_value << 3;
  hash_value ^= hash_value >> 11;
  hash_value += hash_value << 15;
  return hash_value % bucket_count;
}

// ====================================================================================

// =======================function definations ================================
// prints the help message
// if error is true first prints the error message then prints the help message
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
int read_file(FILE *fp1, FILE *fp2, char *filenames[2]) {
  fp1 = fopen(filenames[0], "r");
  if (fp1 == NULL) {
    printf("Error opening file %s. Error: %s\n", filenames[0], strerror(errno));
    return -1;
  }

  fp2 = fopen(filenames[1], "r");
  if (fp2 == NULL) {
    printf("Error opening file %s. Error: %s\n", filenames[1], strerror(errno));
    return -1;
  }
  return 0;
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
  if (read_file(fp1, fp2, argv + 1) == -1) {
    return 1;
  }
  return 0;
}
