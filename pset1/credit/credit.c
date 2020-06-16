// Validation checker for credit card number
#include <cs50.h>
#include <stdio.h>

long get_number(void);

int main(void)
{
    long n = get_long("Number: ");
    int sum_single = 0;
    int sum_double = 0;
    int cc_id = 0;
    int cc_len = 0;
    while (n != 0)
    {
        // Sum the digit without multiplying it by 2
        sum_single += n % 10;

        // Check to see if this is the last digit in iteration
        if (n / 10 < 100 && n / 10 > 9)
        {
            cc_id = n / 10;
        }
        else
        {
            ;
        }
        // Add counter to check the length of the digit
        cc_len ++;
        // Move to the next iteration
        n /= 10;

        // Sum the other digits after multiplying it by 2
        int digit_double = n % 10 * 2;
        int sum_thisdouble = 0;
        while (digit_double != 0)
        {
            sum_thisdouble += digit_double % 10;
            digit_double /= 10;
        }
        sum_double += sum_thisdouble;

        // Check to see if this is the last digit in iteration
        if (n / 10 < 100 && n / 10 > 9)
        {
            cc_id = n / 10;
        }
        else
        {
            ;
        }
        // Add counter to check the length of the digit
        cc_len ++;
        // Move to the next iteration
        n /= 10;

    }

    int sum_all = sum_single + sum_double;

    // Last validation for the credit card
    string status;
    if (sum_all % 10 != 0)
    {
        status = "INVALID";
    }
    else if (cc_len < 13)
    {
        status = "INVALID";
    }
    else if (cc_id == 34 || cc_id == 37)
    {
        status = "AMEX";
    }
    else if (cc_id > 39 && cc_id < 50)
    {
        status = "VISA";
    }
    else if (cc_id > 50 && cc_id < 56)
    {
        status = "MASTERCARD";
    }
    else
    {
        status = "INVALID";
    }
    printf("%s\n", status);
}