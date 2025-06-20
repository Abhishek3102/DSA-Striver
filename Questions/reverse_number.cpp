#include <iostream>
using namespace std;
void reverseNum()
{
    int N;
    int reverseNumber = 0;
    cout << "Enter the number N: ";
    cin >> N;
    int count = 0;
    while (N > 0)
    {
        int lastDigit = N % 10; // if N = 5546, this will give 6
        cout << "Last digit : " << lastDigit << endl;
        N = N / 10; // if N = 5546, this will give 554

        // this step allows the next number to get added into the previous number
        // for eg, the first result is 9 and second is 8
        // so to get 8 after 9, multiply 9 by 10 and add 8 to it
        reverseNumber = (reverseNumber * 10) + lastDigit;
        cout << "The reverse number is : " << reverseNumber;
    }
    cout << endl;
}

int main()
{
    int t;
    cout << "Enter number of test cases : ";
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        reverseNum();
    }
}