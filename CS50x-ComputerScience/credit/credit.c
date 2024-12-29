#include <cs50.h>
#include <stdio.h>

long power(int num, int i)
{
    return (i != 0 ? num * power(num, i - 1) : 1);
}

int checkDigit(long num)
{
    int i = 0;
    while (num != 0)
    {
        num /= 10;
        i++;
    }
    return i;
}

int main(void)
{
    int total = 0;
    long cardNumber = get_long("Number: ");
    long sample = cardNumber;
    int front = 0;
    int second = 0;
    int digit = checkDigit(cardNumber);
    for (int i = 1; i <= digit; i++)
    {
        int adder = (sample % 10);
        total += ((i % 2 == 0) ? ((2 * adder) % 10 + (2 * adder) / 10) : adder);
        sample /= 10;
        second = front;
        front = adder;
    }
    if ((total % 10) == 0)
    {
        switch (digit)
        {
            case 13:
            case 16:
                if (front == 4)
                {
                    printf("VISA\n");
                }
                else if (front == 5 && second <= 5 && second >= 1)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 15:
                if (front == 3)
                {
                    if (second == 7 || second == 4)
                        printf("AMEX\n");
                    else
                        printf("INVALID\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
