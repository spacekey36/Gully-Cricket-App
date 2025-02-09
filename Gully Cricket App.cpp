#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Team {
public:
    string name;
    string players[3];
    int totalRuns;
};

void welcomeUsers();
void displayPlayers(Team teamA, Team teamB);
void selectBatsmanAndBowler(Team &battingTeam, Team &bowlingTeam);
void startInning(int inning, Team &battingTeam, Team &bowlingTeam);
int playInning(Team &battingTeam, Team &bowlingTeam);
void displayScore(Team &team);
void decideWinner(Team &teamA, Team &teamB);

int main() {
    Team teamA = {"TeamA", {"PlayerA1", "PlayerA2", "PlayerA3"}, 0};
    Team teamB = {"TeamB", {"PlayerB1", "PlayerB2", "PlayerB3"}, 0};

    welcomeUsers();

    displayPlayers(teamA, teamB);

    startInning(1, teamA, teamB);
    teamA.totalRuns = playInning(teamA, teamB);
    displayScore(teamA);

    startInning(2, teamB, teamA);
    teamB.totalRuns = playInning(teamB, teamA);
    displayScore(teamB);

    decideWinner(teamA, teamB);

    return 0;
}

void welcomeUsers() {
    cout << "Welcome to Gully Cricket!\n";
}

void displayPlayers(Team teamA, Team teamB) {
    cout << "\nTeamA Players:\n";
    for (int i = 0; i < 3; i++) {
        cout << teamA.players[i] << endl;
    }

    cout << "\nTeamB Players:\n";
    for (int i = 0; i < 3; i++) {
        cout << teamB.players[i] << endl;
    }
}

void selectBatsmanAndBowler(Team &battingTeam, Team &bowlingTeam) {
    srand(time(0));

    int batsmanIndex = rand() % 3;
    int bowlerIndex = rand() % 3;

    cout << "\nBatsman: " << battingTeam.players[batsmanIndex] << endl;
    cout << "Bowler: " << bowlingTeam.players[bowlerIndex] << endl;
}

void startInning(int inning, Team &battingTeam, Team &bowlingTeam) {
    cout << "\nStarting Inning " << inning << endl;
    selectBatsmanAndBowler(battingTeam, bowlingTeam);
}

int playInning(Team &battingTeam, Team &bowlingTeam) {
    int totalRuns = 0;
    srand(time(0));

    for (int ball = 1; ball <= 6; ball++) {
        int runs = rand() % 7;
        totalRuns += runs;
        cout << "Ball " << ball << ": " << runs << " runs\n";
    }

    return totalRuns;
}

void displayScore(Team &team) {
    cout << "\n" << team.name << " scored " << team.totalRuns << " runs.\n";
}

void decideWinner(Team &teamA, Team &teamB) {
    if (teamA.totalRuns > teamB.totalRuns) {
        cout << "\nTeamA won the match!\n";
    } else if (teamA.totalRuns < teamB.totalRuns) {
        cout << "\nTeamB won the match!\n";
    } else {
        cout << "\nThe match ended in a tie!\n";
    }
}
