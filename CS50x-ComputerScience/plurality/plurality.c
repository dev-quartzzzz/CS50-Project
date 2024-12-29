#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[9];
int candidate_count = 0;

// check vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// print the winner name
void print_winner(void)
{
    int higher = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (higher < candidates[i].votes)
        {
            higher = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == higher) && (candidates[i].name != NULL))
            printf("%s\n", candidates[i].name);
    }
}

int main(int argc, string *argv)
{
    while (true)
    {
        if (argv[candidate_count + 1] == NULL)
            break;
        if (candidate_count > 9 && argv[candidate_count + 1] != NULL)
        {
            return 1;
        };
        candidates[candidate_count].name = argv[candidate_count + 1];
        candidates[candidate_count].votes = 0;
        candidate_count++;
    }

    int voting = get_int("Number of voters: ");
    for (int i = 0; i < voting; i++)
    {
        string name = get_string("Vote: ");
        if (vote(name) == false)
        {
            printf("Invalid vote.\n");
        }
    }
    print_winner();
    return 0;
}
