#include <stdint.h>
#include <assert.h>
#include <stdio.h>

/*
A simple solution that works in O(n) time.
loop over the array and check for each element if it is greater than its neighbors or not
*/
int simple_soln(int64_t arr[], uint64_t arr_size) {
    assert(arr_size > 0);
    // if its just a single element return it
    if (arr_size == 1) return 0;
    // check for first element; is peak if its greater than 2nd element
    if (arr[0] > arr[1]) return 0;
    // check for last element; is peak if its greater than 2nd last element
    if (arr[arr_size-1] > arr[arr_size-2]) return arr_size - 1;
    for (int i=1; i<arr_size-2; i++) {
        if ( (arr[i] > arr[i-1]) && (arr[i] > arr[i+1]) ) return i;
    }
    return -1;
}

int recursive_soln(int64_t arr[], uint64_t arr_size) {
    assert(arr_size > 0);
    // if its just a single element return it
    if (arr_size == 1) return 0;
    // check for first element; is peak if its greater than 2nd element
    if (arr[0] > arr[1]) return 0;
    // check for last element; is peak if its greater than 2nd last element
    if (arr[arr_size-1] > arr[arr_size-2]) return arr_size - 1;

    // recursive step
    uint64_t mid = arr_size / 2;
    if ( (arr[mid] > arr[mid - 1]) && (arr[mid] > arr[mid + 1]) ) return mid;
    int left = recursive_soln(arr, mid);
    if (left != -1) {
        if (left != mid-1) return left;
        if (arr[left] > arr[mid]) return left;
    }
    int right = recursive_soln(arr + mid + 1, arr_size - mid - 1);
    if (right != -1) {
        if (right != 0) return mid + right + 1;
        if (arr[right + mid + 1] > arr[mid]) {
            printf("mid: %ld\n", mid);
            return right + mid + 1;
        }
    }
    return -1;
}



int main() {
    int64_t arr[] = {1, 2, 3, 4, 5, 6, 1};
    printf("soln: %d\n", recursive_soln(arr, 7));
}
