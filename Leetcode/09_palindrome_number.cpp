class Solution
{
public:
    bool isPalindrome(int x)
    {
        long long reverseNumber = 0;
        int ogX = x; // here a new variable and value of x is stored in that variable as a copy to check with the reversed number at the end, bcoz after all operations the original x will be down to 0.
        while (x > 0)
        {
            int lastDigit = x % 10;
            x = x / 10;

            reverseNumber = (reverseNumber * 10) + lastDigit;
        }
        if (ogX == reverseNumber)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
