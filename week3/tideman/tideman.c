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
int check_now;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int check_circle(int n);

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
    // TODO

    // 1. 判斷 vaild
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            // 2. valid --> update
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

    // 二維preferences
    // [i][j] = # of prefer i than j
    // we got ranks = {3, 1, 0, 2}; etc.

    // 1. for [0] to [n-1]
    for (int i = 0; i < candidate_count; i++)
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
    // put winner / loser into pair

    // 1. define winner / loser
    //    using preferences

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
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
    // sort
    // 1. compute strengh
    int str[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        str[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    // 2. sort
    // bubble sort
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (str[j] < str[j + 1])
            {
                pair tmp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = tmp;
                int tmp1 = str[j];
                str[j] = str[j + 1];
                str[j + 1] = str[j];
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // 1. update locked using sorted pair
    for (int i = 0; i < pair_count; i++)
    {
        // most strength first change
        locked[pairs[i].winner][pairs[i].loser] = true;

        // check Valid for each candidate have cycle
        check_now = pairs[i].winner;  // record the winner (added to the graph)

        if (check_circle(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

int check_circle(int n)
{
    // check
    for (int i = 0; i < candidate_count; i++)
    {
        
        int flag = 0;
        if (locked[n][i])
        {
            // check equal
            if (i == check_now)
            {
                flag = 1;
            }
            else
            {
                flag = check_circle(i);
            }
        }
        if (flag)
        {
            return 1;
        }
    }
    return 0;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    // 1. find the source
    // its column have to all zero

    for (int col = 0; col < candidate_count; col++)
    {
        int flag = 0;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col])
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            printf("%s\n", candidates[col]);
            return;
        }
    }

    return;
}