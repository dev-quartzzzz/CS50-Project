#include <stdio.h>

int main(void)
{
    int num;
    do
    {
        printf("Height: ");
        scanf("%d", &num);
    }
    while (num < 1 || num > 8);

    for (int i = 0; i < num; i++)
    {
        for (int j = num - 1; j > i; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
