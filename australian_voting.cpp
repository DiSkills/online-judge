#include <stdio.h>

#define MAX_NAME_SIZE 80+1
#define MAX_CANDIDATES_NUMBER 20
#define MAX_BALLOTS_SIZE 1000

class Voting {
    struct Candidate {
        char name[MAX_NAME_SIZE];
        unsigned int votes;
        bool excluded;
    };
    struct Ballot {
        unsigned int rank[MAX_CANDIDATES_NUMBER];
    };
    Candidate candidates[MAX_CANDIDATES_NUMBER];
    Ballot ballots[MAX_BALLOTS_SIZE];
    unsigned int ncandidates, nballots;
public:
    Voting();
    void Calculate();
private:
    void AddCandidate();
    void AddBallot();
    static bool IsBallot(int c) { return c != EOF && c != '\n'; }

    void ResetVotes() {
        for (unsigned int i = 0; i < ncandidates; i++)
            candidates[i].votes = 0;
    }
    void RecalculateVotes();
    void MinMax(unsigned int &min, unsigned int &max) const;
    void ExcludeCandidates(unsigned int n) {
        for (unsigned int i = 0; i < ncandidates; i++)
            if (candidates[i].votes == n) candidates[i].excluded = true;
    }
};

void Voting::AddCandidate()
{
    Candidate &candidate = candidates[ncandidates];
    candidate.votes = 0;
    candidate.excluded = false;

    int c;
    char *name = candidate.name;
    while ((c = getchar()) != '\n') {
        *name = c;
        name++;
    }
    *name = '\0';
    ncandidates++;
}

void Voting::AddBallot()
{
    for (unsigned int i = 0; i < ncandidates; i++) {
        unsigned int n;
        scanf("%u", &n);
        ballots[nballots].rank[i] = n - 1;
    }
    nballots++;
    getchar();
}

Voting::Voting() : ncandidates(0), nballots(0)
{
    unsigned int n;
    for (scanf("%u", &n), getchar(); n > 0; n--) {
        AddCandidate();
    }
    int c;
    while (IsBallot(c = getchar())) {
        ungetc(c, stdin);
        AddBallot();
    }
}

void Voting::RecalculateVotes()
{
    ResetVotes();
    for (unsigned int i = 0; i < nballots; i++) {
        unsigned int pos = 0;
        while (candidates[ballots[i].rank[pos]].excluded) {
            pos++;
        }
        candidates[ballots[i].rank[pos]].votes++;
    }
}

void Voting::MinMax(unsigned int &min, unsigned int &max) const
{
    max = 0;
    min = MAX_BALLOTS_SIZE;
    for (unsigned int i = 0; i < ncandidates; i++) {
        if (candidates[i].excluded) {
            continue;
        }
        unsigned int votes = candidates[i].votes;
        if (votes < min) {
            min = votes;
        }
        if (votes > max) {
            max = votes;
        }
    }
}

void Voting::Calculate()
{
    unsigned int min, max;
    for (;;) {
        RecalculateVotes();
        MinMax(min, max);
        if (max == min || max >= nballots / 2.0) {
            break;
        }
        ExcludeCandidates(min);
    }
    for (unsigned int i = 0; i < ncandidates; i++) {
        if (candidates[i].votes == max) {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main()
{
    unsigned int n;
    scanf("%u", &n);
    for (unsigned int i = 0; i < n; i++) {
        Voting voting;
        if (i > 0) {
            putchar('\n');
        }
        voting.Calculate();
    }
    return 0;
}
