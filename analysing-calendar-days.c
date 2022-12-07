#include <stdbool.h>
#include <stdio.h>

// Checks if it's a leap year
bool checkLeapYear(int year) {

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if(year % 400 == 0) {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;

}

// Returns how many Fridays fell on the fifth of the month during the nineteenth and twentieth centuries (1 Jan 1801 to 31 Dec 2000) given the dates in the question text
int howManyDays() {

    // Length in days for each month Jan, Feb, Mar.. in a common year
    int monthLength[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Storing current date as we count backwards..
    struct fullDate {
        int date[3];
        int day;
    } currentDate;

    currentDate.date[0] = 24; currentDate.date[1] = 3; currentDate.date[2] = 2002;
    currentDate.day = 3;

    int count = 0;
    bool flagDecrease = true;

    // Continue going backwards until the day before 1 Jan 1801 (31 Dec 1800) is reached
    while (currentDate.date[0] != 31 || currentDate.date[1] != 12 || currentDate.date[2] != 1800) {
     
        // Check if it's a Friday on the 5th of the month
        if (currentDate.date[0] == 5 && currentDate.day == 5) {
            // Check if the year is not 2001 or higher (counting period starts from 31 Dec 2000)
            if (currentDate.date[2] < 2001) {
                count++;
            }
        }

        // Decrease date by 1 day following all the calendar rules

        // Decreasing year in case of 1 Jan ____
        if (currentDate.date[1] == 1 && currentDate.date[0] == 1) {
            currentDate.date[0] = 31; currentDate.date[1] = 12; currentDate.date[2]--;

            // Set flag as day has already been decreased
            flagDecrease = false;
        }

        // Decreasing month in case of 1 ___ ____
        if (currentDate.date[0] == 1) {

            // Checking if it's a leap year if it's turning Feb
            if (currentDate.date[1] == 3 && checkLeapYear(currentDate.date[2])) {
                currentDate.date[0] = 29;
            }

            // Any other case follows the table for common years
            else {
                // To get the correct number of days for the corresponding month index is decreased by 2 (because month hasn't been decreased yet)
                currentDate.date[0] = monthLength[currentDate.date[1] - 2];
            }

            // Decreasing the month
            currentDate.date[1]--;

            // Set flag as day has already been decreased
            flagDecrease = false;
        }

        // Decreasing day at every other iteration (day hasn't been decreased yet)
        if (flagDecrease) {
            currentDate.date[0]--;
        }
        else {
            // Reset flag to true
            flagDecrease = true;
        }

        // Updating day of the week
        if (currentDate.day > 1) {
            currentDate.day--;
        }
        else {
            currentDate.day = 7;
        }
        
    }

    return count;

}

int main () {

   howManyDays();
 
   return 0;
}
