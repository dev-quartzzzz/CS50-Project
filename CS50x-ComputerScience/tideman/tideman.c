#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int index_candidate = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i] == name)
        {
            index_candidate = i;
            break;
        }
    }
    if (index_candidate == -1)
        return false;
    for (int i = 0; i < rank; i++)
    {
        if (ranks[i] == index_candidate)
        {
            return false;
        }
    }
    ranks[rank] = index_candidate;
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // iterate in ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // find index of candidate
        int winner_index = ranks[i];

        // check all loser
        for (int j = i + 1; j < candidate_count; j++)
        {
            int loser_index = ranks[j];
            preferences[winner_index][loser_index] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int strength = preferences[i][j] - preferences[j][i];
            if (strength > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (strength < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int max_value = preferences[pairs[i].winner][pairs[i].loser] -
                        preferences[pairs[i].loser][pairs[i].winner];
        int max_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int temp_dif = preferences[pairs[j].winner][pairs[j].loser] -
                           preferences[pairs[j].loser][pairs[j].winner];
            if (max_value < temp_dif)
            {
                max_index = j;
            }
        }
        pair temp = pairs[i];
        pairs[i] = pairs[max_index];
        pairs[max_index] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!cycle(winner, loser))
            locked[winner][loser] = true;
        // check that when loser is winner there will be cycle to the winner or not
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int falsy = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
                falsy++;
        }
        if (falsy == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool cycle(int winner, int loser)
{
    // alteration of recursion
    if (winner == loser) return true;
    for (int i = 0; i < candidate_count; i++)
    {
        if ( locked[loser][i] && cycle(winner, i))
            return true;
    }
    return false;
}
