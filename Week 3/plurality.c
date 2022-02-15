#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;
int voter_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(name, candidates[a].name) == 0)
        {
            candidates[a].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string ca_n[candidate_count];
    int ca_v[candidate_count];
    for (int e = 0; e < candidate_count; e++) // making a new array with the names and total votes
    {
        ca_v[e] = candidates[e].votes;
        ca_n[   e] = candidates[e].name;
    }
    for (int b = 0; b < candidate_count - 1; b++) // selection sort of the total votes
    {
        int min_pos = b;
        for (int c = b + 1; c < candidate_count; c++)
        {
            if (ca_v[c] < ca_v[min_pos])
            {
                min_pos = c;
            }
            if (min_pos != b)
            {
                int temp = ca_v[b];
                ca_v[b] = ca_v[min_pos];
                ca_v[min_pos] = temp;
                string stemp = ca_n[b];
                ca_n[b] = ca_n[min_pos];
                ca_n[min_pos] = stemp;
            }
        }
    }
    for (int d = 0; d < candidate_count; d++) // checking the biggest count
    {
        if (ca_v[candidate_count - d - 1] > ca_v[candidate_count - d - 2]) // if last after sorted is bigger than second to last
        {
            printf("%s\n", ca_n[candidate_count - d - 1]);
            return;
        }
        else if (ca_v[candidate_count - d - 1] == ca_v[candidate_count - d - 2]) // if last = second to last
        {
            printf("%s\n", ca_n[candidate_count - d - 1]);
        }
    }
    return;
}
