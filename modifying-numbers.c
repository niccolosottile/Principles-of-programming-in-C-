#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool containsDigit(int* number_ptr, int x) {

    // Retrieve value of number from pointer
    int number = *number_ptr;

    // Keep checking digits until no more is left
    while (number != 0) {

        // Check right most digit first
        if (number % 10 == x) {
            return true;
        }

        // Remove right most digit to continue checking
        number = number / 10;

    }

    return false;

}

void removeDigit(int x, int n, int* a_ptr, int* b_ptr){

    // Initialise a as 1 and b as n-1 (increase a and decrease b to get compatible sum) 
    *a_ptr = 1;
    *b_ptr = n - 1;


    while (true) {

        // Check if the digit x is contained in either a or b
        if (!containsDigit(a_ptr, x) && !containsDigit(b_ptr, x)) {

            // If a + b is equal to n we have a set of solutions
            if (*a_ptr + *b_ptr == n) {
                break;
            }

        }

        // Increase a by 1 and decrease b by 1
        (*a_ptr)++;
        (*b_ptr)--;

    }

}

int main () {

    int digit = 7;
    int n = 178;
    int a = 0;
    int b = 0;

    removeDigit(digit, n, &a, &b);

    printf("A: %d\n", a);
    printf("B: %d\n", b);

    return 0;

}
