#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    int n = strlen(argv[1]);

    if (n != 26)
    {
        printf("Key must contain and only contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext:  ");

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (islower(plaintext[i]))
        {
            int letter = (int) plaintext[i] - 97;
            plaintext[i] = tolower(argv[1][letter]);
        }
        else if (isupper(plaintext[i]))
        {
            int letter = (int) plaintext[i] - 65;
            plaintext[i] = toupper(argv[1][letter]);
        }
    }
    printf("ciphertext: %s\n", plaintext);

    return 0;
}
