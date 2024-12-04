#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *input_file = fopen("input.txt", "r");
  if (input_file == NULL) {
    fprintf(stderr, "Error reading input file, err: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  int buff_len = 100000;
  char buffer[buff_len];
  int bytes_read = fread(buffer, sizeof(char), buff_len, input_file);
  int grid[buff_len];
  int rows = 0;
  int cols = 0;
  int count = 0;
  for (int i = 0; i < buff_len; i++)
    grid[i] = 0;

  while (buffer[cols++] != '\n')
    ;
  cols--;

  for (int i = 0, j = 0; i < bytes_read; i++) {
    switch (buffer[i]) {
    case 'X':
      grid[j++] = 1;
      break;
    case 'M':
      grid[j++] = 10;
      break;
    case 'A':
      grid[j++] = 100;
      break;
    case 'S':
      grid[j++] = 1000;
      break;
    case '\n':
      rows++;
      break;
    default:
      j++;
    }
  }

  // horizontal
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols - 3; c++) {
      int i = r * cols + c;
      int sum = grid[i] + 2 * grid[i + 1] + 3 * grid[i + 2] + 4 * grid[i + 3];
      if (sum == 1234 || sum == 4321) {
        // printf("horizontal starting at: %d\n", i);
        count++;
      }
    }
  }

  // vertical
  for (int r = 0; r < rows - 3; r++) {
    for (int c = 0; c < cols; c++) {
      int i = r * cols + c;
      int sum = grid[i] + 2 * grid[i + cols] + 3 * grid[i + 2 * cols] +
                4 * grid[i + 3 * cols];
      if (sum == 1234 || sum == 4321) {
        // printf("vertical starting at: %d\n", i);
        count++;
      }
    }
  }

  // main diagonal
  for (int r = 0; r < rows - 3; r++) {
    for (int c = 0; c < cols - 3; c++) {
      int i = r * cols + c;
      int sum = grid[i] + 2 * grid[i + cols + 1] + 3 * grid[i + 2 * cols + 2] +
                4 * grid[i + 3 * cols + 3];
      if (sum == 1234 || sum == 4321) {
        // printf("main diagonal starting at: %d\n", i);
        count++;
      }
    }
  }

  // other diagonal
  for (int r = 0; r < rows - 3; r++) {
    for (int c = 3; c < cols; c++) {
      int i = r * cols + c;
      int sum = grid[i] + 2 * grid[i + cols - 1] + 3 * grid[i + 2 * cols - 2] +
                4 * grid[i + 3 * cols - 3];
      // printf("other diagonal i: %d, sum: %d\n", i, sum);
      if (sum == 1234 || sum == 4321) {
        // printf("other diagonal starting at: %d\n", i);
        count++;
      }
    }
  }
  printf("no of xmas: %d\n", count);

  return EXIT_SUCCESS;
}
