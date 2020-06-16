// Substitution cipher

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Accepts only if there's 2 argument count
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int key_len = strlen(key);

        // Key must have 26 chars
        if (key_len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int alphabet_len = strlen(alphabet);
            int diff[alphabet_len];

            // Key can only contain alphabetic characters
            for (int i = 0; i < key_len; i++)
            {
                key[i] = toupper(key[i]);
                if (!(isalpha(key[i])))
                {
                    printf("Key must contain 26 alphabetic characters.\n");
                    return 1;
                }
                else
                {
                    // Key have to contain different characters
                    for (int j = i + 1; j < key_len; j++)
                    {
                        key[j] = toupper(key[j]);
                        if (key[i] == key[j])
                        {
                            printf("Key must contain 26 different characters.\n");
                            return 1;
                        }
                    }
                    // Store the key difference with array
                    diff[i] = key[i] - alphabet[i];
                }
            }
            // Get user input for the plain text
            string plain = get_string("plaintext: ");
            int plain_len = strlen(plain);
            int cipher[plain_len];

            printf("ciphertext: ");

            // Iterate every char in plain text
            for (int i = 0; i < plain_len; i++)
            {
                // Convert the char according to the key difference
                for (int j = 0; j < alphabet_len; j++)
                {
                    if (toupper(plain[i]) == alphabet[j])
                    {
                        cipher[i] = plain[i] + diff[j];
                        break;
                    }
                    else
                    {
                        cipher[i] = plain[i];
                    }
                }
                printf("%c", cipher[i]);
            }
            printf("\n");
        }
    }
}