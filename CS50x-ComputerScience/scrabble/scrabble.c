#include <cs50.h>
#include <stdio.h>
#include <string.h>

int scoreCounter(string str)
{
    int arr[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int counter = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] <= 'Z' && str[i] >= 'A')
            counter += arr[str[i] - 'A'];
        if (str[i] >= 'a' && str[i] <= 'z')
            counter += arr[str[i] - 'a'];
    }
    return counter;
}

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");
    int player1Point = 0, player2Point = 0;
    if (scoreCounter(player1) > scoreCounter(player2))
    {
        printf("Player 1 wins!\n");
    }
    else if (scoreCounter(player1) < scoreCounter(player2))
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Ties!\n");
    }
}
