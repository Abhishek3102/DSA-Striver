class Solution
{
public:
    int reverse(int x)
    {
        int reversed = 0;

        if (x == INT_MIN)
        {
            return 0;
        }

        bool isNegative = (x < 0);
        if (isNegative)
        {
            x = -x;
        }

        while (x != 0)
        {
            int lastDigit = x % 10;
            x = x / 10;

            if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && lastDigit > 7))
            {
                return 0;
            }
            reversed = reversed * 10 + lastDigit;
        }
        return isNegative ? -reversed : reversed;
    }
};