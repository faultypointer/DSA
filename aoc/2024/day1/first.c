#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_list(int arr[], int count);

int main() {
  FILE *input_file = fopen("input.txt", "r");
  if (input_file == NULL) {
    fprintf(stderr, "Error reading input file, err: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  int left_list[1000];
  int right_list[1000];
  int count = 0;

  int buff_len = 100000;
  char buffer[buff_len];
  int bytes_read = fread(buffer, sizeof(char), buff_len, input_file);

  for (int i = 0; i < bytes_read;) {
    char c = buffer[i++];
    int num = 0;
    while (c != ' ') {
      num *= 10;
      num += c - '0';
      c = buffer[i++];
    }
    left_list[count] = num;
    while (buffer[i] == ' ' || buffer[i] == '\t')
      i++;

    num = 0;
    c = buffer[i++];
    while (c != '\n') {
      num *= 10;
      num += c - '0';
      c = buffer[i++];
    }
    right_list[count++] = num;
  }

  sort_list(left_list, count);
  sort_list(right_list, count);

  // first part
  int sum = 0;
  for (int i = 0; i < count; i++) {
    int diff = left_list[i] - right_list[i];
    diff = (diff < 0) ? -diff : diff;
    sum += diff;
  }
  printf("sum: %d\n", sum);

  // second part
  int right_index = 0;
  int similarity = 0;
  for (int i = 0; i < count; i++) {
    int num = left_list[i];
    int match = 0;
    for (;;) {
      if (right_list[right_index] > num)
        break;
      else if (right_list[right_index++] == num)
        match++;
    }
    int num_num = 1;
    while (left_list[i + 1] == num) {
      num_num++;
      i++;
    }
    similarity += num_num * num * match;

    if (right_index >= count)
      break;
  }

  printf("similarity: %d\n", similarity);

  return EXIT_SUCCESS;
}

void sort_list(int arr[], int count) {
  for (int i = 0; i < count - 1; i++) {
    int min_index = i;
    for (int j = i; j < count; j++) {
      if (arr[min_index] > arr[j])
        min_index = j;
    }
    int temp = arr[i];
    arr[i] = arr[min_index];
    arr[min_index] = temp;
  }
}
