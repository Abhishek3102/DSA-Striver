#include <iostream>
#include <cmath>
using namespace std;

void find_arm3()
{
    // This for numbers with 3 digits only
    int num;
    int lastDigit, sum = 0;
    // int sum = 0;
    int reverseNumber = 0;
    cout << "enter num : ";
    cin >> num;
    while (num != 0)
    {
        lastDigit = num % 10;
        sum += lastDigit * lastDigit * lastDigit;
        num = num / 10;
        reverseNumber = (reverseNumber * 10) + lastDigit;
    }
    cout << "Rev" << reverseNumber << endl;
    cout << "sum" << sum << endl;
    // cout << sum;
    // if (num == sum)
    // {
    //     cout << sum;
    // }
    // cout << endl;
}

void find_armN()
{
    int num;
    int originalNum, lastDigit, sum = 0, numDigits = 0;
    cout << "Enter num: ";
    cin >> num;

    // Store the original number to compare later
    originalNum = num;

    // Step 1: Calculate the number of digits in the number
    while (num != 0)
    {
        numDigits++;
        num = num / 10;
    }

    // Step 2: Reset num to original value and calculate the sum of digits raised to the power of numDigits
    num = originalNum;
    sum = 0; // Reset sum to 0

    while (num != 0)
    {
        lastDigit = num % 10;             // Get the last digit
        sum += pow(lastDigit, numDigits); // Add the digit raised to the power of numDigits
        num = num / 10;                   // Remove the last digit
    }

    // Output results
    cout << "Sum of powers of digits: " << sum << endl;

    // Check if the number is an Armstrong number
    if (sum == originalNum)
    {
        cout << originalNum << " is an Armstrong number." << endl;
    }
    else
    {
        cout << originalNum << " is NOT an Armstrong number." << endl;
    }
}

int main()
{
    int t;
    cout << "Enter number of test cases : ";
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        find_armN();
    }
}