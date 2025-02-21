#include <cs50.h>
#include <stdio.h>

bool verify(long x);
void decision(bool valid, long no);

int main(void)
{
    long number = get_long("Number: ");

    bool validity = verify(number);
    decision(validity, number);
}

bool verify(long x)
{
    long sum = 0;
    int i = 0;
    long num = x;

    do
    {
        if (i % 2 == 0)
        {
            sum += num % 10;
        }
        else
        {
            long n = (num % 10) * 2;
            if (n > 9)
            {
                n = n % 10 + n / 10;
            }
            sum += n;
        }
        i++;
        num /= 10;
    }
    while (num > 0);

    if (sum % 10 == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void decision(bool valid, long no)
{
    if (valid && (no / 10000000000000 == 34 || no / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (valid && (no / 100000000000000 == 51 || no / 100000000000000 == 52 ||
                       no / 100000000000000 == 53 || no / 100000000000000 == 54 ||
                       no / 100000000000000 == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (valid && (no / 1000000000000 == 4 || no / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
