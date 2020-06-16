// Build the pyramid platform in mario
#include <cs50.h>
#include <stdio.h>

int get_height(void);

void build_platform(int n);

int main(void)
{
    int n = get_height();
    for (int i = 0; i < n; i++)
    {
        // Prefix the platform with gaps
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }

        // Build the first platform
        build_platform(i);

        printf("  ");

        // Build the second platform
        build_platform(i);

        printf("\n");
    }
}

// Get the height of the pyramid
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

// Build the platform
void build_platform(int n)
{
    for (int i = 0; i <= n; i++)
    {
        printf("#");
    }
}