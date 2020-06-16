// Caesar cipher

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Accepts only if there's 2 argument count
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int key_len = strlen(key);

        // First char of argument must not be 0
        if (key[0] == '0')
        {
            printf("Key must be a positive integer\n");
            return 1;
        }
        else
        {
            // Key must contain numeric value only
            for (int i = 0; i < key_len; i++)
            {
                if (!(isdigit(key[i])))
                {
                    printf("Key must be a positive integer\n");
                    return 1;
                }
            }
            // Convert the argument from string to integer
            int diff = atoi(key);

            string plain = get_string("plaintext: ");
            int plain_len = strlen(plain);
            int cipher[plain_len];

            printf("ciphertext: ");

            // Iterate every char in plain text
            for (int i = 0; i < plain_len; i++)
            {
                if (isalpha(plain[i]))
                {
                    // Convert the char according to the key difference
                    // Keep in mind the ascii descimall ascii char
                    if (isupper(plain[i]))
                    {
                        cipher[i] = (plain[i] - 65 + diff) % 26 + 65;
                    }
                    else
                    {
                        cipher[i] = (plain[i] - 97 + diff) % 26 + 97;
                    }
                }
                else
                {
                    cipher[i] = plain[i];
                }
                printf("%c", (char) cipher[i]);
            }
            printf("\n");
        }
    }
}