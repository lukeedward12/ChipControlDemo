#include <stdio.h>

// Function under test. Defined somewhere in your project files.
int function_under_test() {
  // This function would usually do something useful.
  // For this example, let's just have it return 42.
  return 42;
}

int main() {
  // Run our test
  if (function_under_test() != 42) {
    printf("Test failed!\n");
    return 1;
  } else {
    printf("Test passed!\n");
    return 0;
  }
}
