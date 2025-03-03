#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score(string input);

int main(void)
{
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    int score1 = score(input1);
    int score2 = score(input2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(string input)
{
    int s = 0;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        input[i] = toupper(input[i]);

        if (input[i] == 'A' || input[i] == 'E' || input[i] == 'I' || input[i] == 'L' ||
            input[i] == 'N' || input[i] == 'O' || input[i] == 'R' || input[i] == 'S' ||
            input[i] == 'T' || input[i] == 'U')
        {
            s += 1;
        }
        else if (input[i] == 'D' || input[i] == 'G')
        {
            s += 2;
        }
        else if (input[i] == 'B' || input[i] == 'C' || input[i] == 'M' || input[i] == 'P')
        {
            s += 3;
        }
        else if (input[i] == 'F' || input[i] == 'H' || input[i] == 'V' || input[i] == 'W' ||
                 input[i] == 'Y')
        {
            s += 4;
        }
        else if (input[i] == 'K')
        {
            s += 5;
        }
        else if (input[i] == 'J' || input[i] == 'X')
        {
            s += 8;
        }
        else if (input[i] == 'Q' || input[i] == 'Z')
        {
            s += 10;
        }
    }
    return s;
}
