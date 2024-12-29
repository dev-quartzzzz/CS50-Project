// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int i = 0, upl = 0, lol = 0, num = 0, sym = 0;
    while(password[i] != '\0')
    {
        if(password[i] >= 65 && password[i] <= 90) upl++;
        else if(password[i] >= 97 && password[i] <= 122) lol++;
        else if(password[i] >= 48 && password[i] <= 57) num++;
        else sym++;
        i++;
    }
    if(upl && lol && num && sym) return true;
    return false;
}
