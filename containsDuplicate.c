#include <stdbool.h>

// Function to check if an array contains any duplicates
bool containsDuplicate(int* nums, int numsSize) {
    int i = 0;
    int j = 0;

    // Outer loop:pick each element
    for (i = 0; i < numsSize; i++) {
        // Inner loop: compare with every element that comes after
        for (j = i + 1; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                return true; // Duplicate found
            }
        }
    }
    return false; // No duplicates found
}

/*
I learned that I placed the 'return false statement inside the innermost loop, which caused the function to exit too early.
When I moved the statement to the outside loop I realized my mistake.
*/