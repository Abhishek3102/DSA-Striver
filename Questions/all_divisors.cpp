#include <iostream>
#include <cmath>
using namespace std;

void get_all_divisors()
{
    int num;
    int count = 0;
    cout << "Enter num :";
    cin >> num;

    if (num <= 0)
    {
        cout << "Please provide positive integer only" << endl;
        return;
    }

    cout << "The divisors of " << num << " are : " << endl;

    for (int i = 1; i <= num; i++)
    {

        if (num % i == 0)
        {
            cout << i << " ";
            count += 1;
            cout << endl;
        }
    }
    cout << "The number of divisors of " << num << " are : " << count << endl;
}

int main()
{
    int t;
    cout << "Enter number of test cases : ";
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        get_all_divisors();
    }
    return 0;
}