#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool *ptrT = &locked[1][1];
bool *ptrF = &locked[1][1];

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
bool circle(int beg, int end);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            int *p = &ranks[rank];
            *p = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        for (int m = 1; m < candidate_count - k; m++)
        {
            int *p1 = &preferences[ranks[k]][ranks[k + m]];
            *p1 += 1;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int l = 0; l < candidate_count; l++)
    {
        for (int o = 0; o < candidate_count; o++)
        {
            if (l != o && preferences[l][o] > preferences[o][l])
            {
                int *p2 = &pair_count;
                *p2 += 1;
                p2 = &pairs[pair_count - 1].winner;
                *p2 = l;
                p2 = &pairs[pair_count - 1].loser;
                *p2 = o;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength [pair_count];
    for (int p = 0; p < pair_count; p++)
    {
        strength[p] = preferences[pairs[p].winner][pairs[p].loser] - preferences[pairs[p].loser][pairs[p].winner];
    }
    for (int q = 0; q < pair_count; q++)
    {
        for (int r = 0; r < pair_count - q - 1; r++)
        {
            int comp1 = strength[r];
            int comp2 = strength[r + 1];
            int compp11 = pairs[r].winner;
            int compp22 = pairs[r + 1].winner;
            int *compp1 = &pairs[r].winner;
            int *compp2 = &pairs[r + 1].winner;
            int compp111 = pairs[r].loser;
            int compp222 = pairs[r + 1].loser;
            int *comp11 = &pairs[r].loser;
            int *comp22 = &pairs[r + 1].loser;
            if (comp2 > comp1)
            {
                strength[r] = comp2;
                strength[r + 1] = comp1;
                *compp1 = compp22;
                *compp2 = compp11;
                *comp11 = compp222;
                *comp22 = compp111;
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
        if (!circle(pairs[i].winner, pairs[i].loser)) // if not circle
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // lock the pair
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int w = 0; w < candidate_count; w++)//check column
    {
        for (int x = 0; x < candidate_count; x++)//check row
        {
            if (locked[x][w] == true)
            {
                x = candidate_count;
                break;
            }
            else if (locked[x][w] == false && x == candidate_count - 1)
            {
                printf("%s\n", candidates[w]);
            }
        }
    }
    return;
}

bool circle(int beg, int end)
{
    if (end == beg) // if the end we want to attach is the same as the beginning
    {
        return true;
    }
    for (int kk = 0; kk < candidate_count; kk++)
    {
        if (locked[end][kk] == true) // if end locked
        {
            if (circle(beg, kk) == true) // if start locked
            {
                return true; // is circle
            }
        }
    }
    return false;
}



//GRAVEYARD of failed algorithms:

// bool circle()
// {
//     int checkarr[pair_count][2]; //lines 194 to 205: to make sure no cycles are locked
//     for (int s = 0; s < pair_count; s++)
//     {
//         for (int t = 0; t <= s; t++)
//         {
//             if (pairs[s].loser == checkarr[t][0])
//             {
//                 for (int u = 0; u <= s + 1; u++)
//                 {
//                     if (checkarr[t][1] == pairs[u].winner && pairs[s].winner == pairs[u].loser)
//                     {
//                         checkarr[s][0] = 0;
//                         checkarr[s][1] = 0;
//                         u = s;
//                         t = s;
//                     }
//                 }
//             }
//             else
//             {
//                 checkarr[s][0] = pairs[s].winner;
//                 checkarr[s][1] = pairs[s].loser;
//             }
//         }
//     }
//     for (int i=0; i<pair_count; i++)
//     {
//         if (checkarr[i][0] != checkarr[i][1])
//         {
//         printf("%d %d\n", checkarr[i][0], checkarr[i][1]);
//         }
//     }
//     for (int v = 0; v < pair_count; v++)
//     {
//         if (checkarr[v][0] != checkarr[v][1])
//         {
//             *ptrT = &locked[checkarr[0][v]];
//             *ptrF = &locked[checkarr[1][v]];
//             *ptrT = TRUE;
//             *ptrF = FALSE;
//         }
//     }
//     return;
// }


// void print_winner(void)
// {
//     int edges[candidate_count];
//     for (int z = 0; z < candidate_count; z++)
//     {
//         edges[z] = 0;
//     }
//     for (int w = 0; w < candidate_count; w++)
//     {
//         for (int x = 0; x < candidate_count; x++)
//         {
//             if (locked[w][x] == true)
//             {
//                 edges[w]++;
//             }
//         }
//     }
//     int biggestp = biggest(edges);
//     int jj = 0;
// }
