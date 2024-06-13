// Runoff Voting System, By Roberto Thompson, with the help of distribution code from the CS50x Program
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // iterates through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate length are the same (strlen)
        if (strcmp(candidates[i].name, name) == 0)
        {
            // update vote for that specific candidate
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // iterates through voters
    for (int i = 0; i < voter_count; i++)
    {
        // iterates through candidates
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            // if candidate is eliminated
            if (!candidates[candidate_index].eliminated)
            {
                // vote for their 2nd, 3rd... preferred candidate on the list
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // the condition that needs to be passed for the candidate to win (as in number of votes)
    int majority = voter_count / 2 + 1;

    // iterates through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if greater or equal to the voter majority
        if (candidates[i].votes >= majority)
        {
            // print the winner
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = __INT_MAX__;

    // iteration
    for (int i = 0; i < candidate_count; i++)
    {
        // if less then the current min votes
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            // replace the minimum with the current iteration of i
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // iteration
    for (int i = 0; i < candidate_count; i++)
    {
        // if every candidate has the same amount of votes
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // iteration
    for (int i = 0; i < candidate_count; i++)
    {
        // if the current candidate out of the rest has the least amount of votes
        if (candidates[i].votes == min)
        {
            // eliminate them
            candidates[i].eliminated = true;
        }
    }

    return;
}
