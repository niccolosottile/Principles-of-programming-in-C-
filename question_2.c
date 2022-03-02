#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    // Seed the randomizer (only called once)
    srand(time(NULL));

    while (true) {

        // Assign a and b a random value between 1 and n - 1
        *a_ptr = rand() % (n - 1) + 1;
        *b_ptr = rand() % (n - 1) + 1;

        // Check if the digit x is contained in either a or b
        if (containsDigit(a_ptr, x) == 0 && containsDigit(b_ptr, x) == 0) {

            // If a + b is equal to n we have a set of solutions
            if (*a_ptr + *b_ptr == n) {
                break;
            }

        }

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