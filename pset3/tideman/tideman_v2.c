#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
pair;

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
    // Query for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
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
    // TODO
    int swapcounter = -1;
    while (swapcounter != 0)
    {
        swapcounter = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <  preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair tmp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = tmp;
                swapcounter++;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair[%i]: Winner = %s, Loser = %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
    }
    // Iterate each pairs
    for (int i = 0; i < pair_count; i++)
    {
        bool cycle = false;
        int j = 0;
        int count = 0;
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        while (j < candidate_count)
        {
            if (locked[loser][j] == true)
            {
                if (j == pairs[i].winner)
                {
                    cycle = true;
                    printf("Did not lock %s -> %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
                    break;
                }
                else
                {
                    loser = j;
                    j = 0;
                }
            }
            else
            {
                if (count == candidate_count)
                {
                    j++;
                    count = 0;
                }
                else
                {
                    count++;
                }
            }
        }

        if (cycle == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("Locked %s -> %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
    }
    return;
}

/* bool check_graph(int winner, int loser) */
/* { */
/*     for (int i = 0; i < candidate_count; i++) */
/*     { */
/*         if (locked[loser][i] == true) */
/*         { */
/*             if (i == winner) */
/*             { */
/*                 return true; */
/*             } */
/*             else */
/*             { */
/*                 check_graph(loser, i); */
/*             } */
/*         } */
/*     } */
/* } */

// Print the winner of the election
void print_winner(void)
{
    // TODO
    printf("\n");
    // Iterate every candidate pairing
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If it's locked
            // If the loser is a winner on other pairings, it's the actual winner
            if (locked[i][j] == true)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[k][i] == true)
                    {
                        printf("Winner = %s\n", candidates[k]);
                        return;
                    }
                }
                printf("Winner = %s\n", candidates[pairs[0].winner]);
                return;
            }
        }
    }
}
