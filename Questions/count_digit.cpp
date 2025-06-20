#include <iostream>
using namespace std;
void countDig()
{
    int N;
    cout << "Enter the number N: ";
    cin >> N;
    int count = 0;
    while (N > 0)
    {
        int lastDigit = N % 10; // if N = 5546, this will give 6
        cout << "Last digit : " << lastDigit << endl;
        N = N / 10; // if N = 5546, this will give 554
        count += 1;
        cout << "The number of digits in number is : " << count;
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
        countDig();
    }
}