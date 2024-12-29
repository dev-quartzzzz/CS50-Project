#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int search(char k, string upper, string lower)
{
    return (strchr(upper, k) == NULL && strchr(lower, k) == NULL) ? 0 : 1;
}

int hasNumInKey(string k)
{
    int size = strlen(k);
    for (int i = 0; i < size; i++)
    {
        if (!(isalpha(k[i])))
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, string argv[])
{
    // validate key
    string key = argv[1];
    char upper[27];
    char lower[27];
    // number of argument must be 2 (command & key)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int size = strlen(key);
    if (size != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    if (hasNumInKey(key))
    {
        printf("Key must only contain alphabetic characters\n");
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        if (search(key[i], upper, lower))
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        else
        {
            upper[i] = toupper(key[i]);
            lower[i] = tolower(key[i]);
        }
    }
    upper[26] = '\0';
    lower[26] = '\0';
    string plain = get_string("plaintext: ");
    int plain_size = strlen(plain);
    char cipherText[plain_size + 1];
    for (int i = 0; i < strlen(plain); i++)
    {
        if (plain[i] >= 'A' && plain[i] <= 'Z')
        {
            cipherText[i] = upper[plain[i] - 'A'];
            // cipherText = strcpy(cipherText, upper[plain[i]-'A']);
        }
        else if (plain[i] >= 'a' && plain[i] <= 'z')
        {
            cipherText[i] = lower[plain[i] - 'a'];
            // cipherText = strcpy(cipherText, lower[plain[i]-'A']);
        }
        else
        {
            cipherText[i] = plain[i];
            // cipherText = strcpy(cipherText, plain[i]);
        }
    }
    cipherText[plain_size] = '\0';
    printf("ciphertext: %s\n", cipherText);
}
