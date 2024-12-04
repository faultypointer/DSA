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

  // buffer[bytes_read] = '\0';
  // printf("%s\n", buffer);

  for (int i = 0, j = 0; i < bytes_read; i++) {
    switch (buffer[i]) {
    case 'M':
      grid[j++] = 1;
      break;
    case 'A':
      grid[j++] = 10;
      break;
    case 'S':
      grid[j++] = 100;
      break;
    case '\n':
      rows++;
      break;
    default:
      j++;
    }
  }
  // printf("rows: %d, cols: %d\n", rows, cols);

  for (int r = 0; r < rows - 2; r++) {
    for (int c = 0; c < cols - 2; c++) {
      // printf("%5d", grid[r * cols + c]);
      int c1 = r * cols + c;
      int c2 = c1 + 2;
      int c3 = c1 + 2 * cols;
      int c4 = c3 + 2;
      int center = c1 + 1 + cols;
      int main_diag_sum = grid[c1] + grid[c4];
      int other_diag_sum = grid[c2] + grid[c3];
      // printf("for i: %d\tcenter: %d, c1: %d, c2: %d, c3: %d, c4: %d\n", c1,
      //        grid[center], grid[c1], grid[c2], grid[c3], grid[c4]);
      if (grid[center] == 10 && main_diag_sum == 101 && other_diag_sum == 101) {
        // printf("horizontal starting at: %d\n", i);
        count++;
      }
    }
    // printf("\n");
  }

  printf("no of x-mas: %d\n", count);

  return EXIT_SUCCESS;
}
