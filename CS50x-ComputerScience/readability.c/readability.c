#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string str = get_string("Text: ");
    int word = 1, letter = 0, sentence = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
        if (str[i] == ' ')
        {
            word++;
        }
        else if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            sentence++;
        }
        else if (str[i] <= 'z' && str[i] >= 'a')
        {
            letter++;
        }
        if (i == 0 && letter == 0)
        {
            word--;
            break;
        }
    }
    float L = (float) letter / word * 100;
    float S = (float) sentence / word * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16)
    {
        printf("Grade %d\n", (int) round(index));
    }
    else
    {
        printf("Grade 16+\n");
    }
}
