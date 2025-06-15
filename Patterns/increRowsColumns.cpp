#include <iostream>
#include <string>

using namespace std;
/*
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << "*";
        }
        cout << endl;
    }

    // result :
    // 4
    // *
    // **
    // ***
    // ****
}

*/

void print3(int n)
{
    /*
    Question :
    1
    1 2
    1 2 3
    1 2 3 4
    */
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void print4(int n)
{
    /*
    Question :
    1
    2 2
    3 3 3
    4 4 4 4
    5 5 5 5 5
    6 6 6 6 6 6
    7 7 7 7 7 7 7
    8 8 8 8 8 8 8 8
    */
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

void print5(int n)
{
    /*
    Question :
    4
    * * * *
    * * *
    * *
    *

    */
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i + 1; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }
}

// same print5(n) in another way
/*
void print5(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = n; j > 0; j--)  // Start with j = n and decrement
        {
            if (j >= i)  // Only print stars if j is greater than or equal to i
                cout << "* ";
            else
                break;  // Exit the loop once the condition is no longer met
        }
        cout << endl;
    }
}


*/

void print6(int n)
{
    /*
    Question :
    7
    1 2 3 4 5 6 7
    1 2 3 4 5 6
    1 2 3 4 5
    1 2 3 4
    1 2 3
    1 2
    1

    */
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i + 1; j++)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void print7(int n)
{
    /*
    Question :

    5
    *
   ***
  *****
 *******
*********

    */
    for (int i = 0; i < n; i++)
    {
        // space
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }
        // star
        for (int j = 0; j < 2 * i + 1; j++)
        {
            cout << "*";
        }
        // space
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void print8(int n)
{
    /*
    Question :

    5
*********
 *******
  *****
   ***
    *

    */
    for (int i = 0; i < n; i++)
    {
        // space
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        // star
        for (int j = 0; j < 2 * n - (2 * i + 1); j++)
        {
            cout << "*";
        }

        // space
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void print9(int n)
{
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        int stars = i;
        // if (i > n)
        //     stars = 2 * n - 1;

        if (i <= n)
            stars = 2 * i - 1; // 1, 3, 5, ..., 2n-1 stars
        else
            stars = 2 * (2 * n - i) - 1;

        for (int j = 1; j <= stars; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        // print7(n);
        // print8(n);
        print9(n);
    }
}

// Combining 7th and 8th pattern, that is printing both together gives :
/*
5
    *
   ***
  *****
 *******
*********
*********
 *******
  *****
   ***
    *
*/