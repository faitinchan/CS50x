#include <stdio.h>

void print_hash(int number);

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1);

    for (int i = 1; i <= height; i++)
    {
        for (int k = 0; k < height - i; k++)
        {
            printf(" ");
        }

        print_hash(i);

        printf("  ");

        print_hash(i);

        printf("\n");
    }
}

void print_hash(int number)
{
    for (int j = 0; j < number; j++)
    {
        printf("#");
    }
}
