#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

class Player {
public:
    string name;
    int runsScored;
    int ballsPlayed;
    int ballsBowled;
    int runsGiven;
    int wicketsTaken;

    Player(string name) {
        this->name = name;
        runsScored = 0;
        ballsPlayed = 0;
        ballsBowled = 0;
        runsGiven = 0;
        wicketsTaken = 0;
    }
};

class Team {
public:
    string teamName;
    vector<Player*> players;
    int totalRuns;
    int totalWickets;
    int totalBallsBowled;

    Team(string teamName) {
        this->teamName = teamName;
        totalRuns = 0;
        totalWickets = 0;
        totalBallsBowled = 0;
    }

    void addPlayer(Player* player) {
        players.push_back(player);
    }
};

class Game {
public:
    vector<string> allPlayers;
    Team* teamA;
    Team* teamB;
    Team* battingTeam;
    Team* bowlingTeam;
    Player* batsman;
    Player* bowler;
    int maxBalls;
    int currentInning;

    Game() {
        allPlayers = {"Virat", "Rohit", "Dhawan", "Rahul", "Pandya", "Bumrah", "Sharma", "Pant", "Jadeja", "Yadav", "Iyer"};
        maxBalls = 6;
        currentInning = 1;
    }

    void welcome() {
        cout << "Welcome to the Virtual Cricket Game - CRIC-IN" << endl;
    }

    void displayAllPlayers() {
        cout << "Available Players:" << endl;
        for (int i = 0; i < allPlayers.size(); i++) {
            cout << i+1 << ". " << allPlayers[i] << endl;
        }
    }

    int takeIntegerInput() {
        int input;
        cin >> input;
        return input;
    }

    bool validateSelectedPlayer(int index, vector<Player*> &teamPlayers) {
        for (auto player : teamPlayers) {
            if (player->name == allPlayers[index-1]) {
                return false;
            }
        }
        return true;
    }

    void selectPlayers() {
        cout << "Select players for Team A and Team B:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Select player " << i+1 << " for Team A: ";
            int playerIndexA = takeIntegerInput();
            while (!validateSelectedPlayer(playerIndexA, teamA->players)) {
                cout << "Player already selected. Choose another: ";
                playerIndexA = takeIntegerInput();
            }
            teamA->addPlayer(new Player(allPlayers[playerIndexA-1]));

            cout << "Select player " << i+1 << " for Team B: ";
            int playerIndexB = takeIntegerInput();
            while (!validateSelectedPlayer(playerIndexB, teamB->players)) {
                cout << "Player already selected. Choose another: ";
                playerIndexB = takeIntegerInput();
            }
            teamB->addPlayer(new Player(allPlayers[playerIndexB-1]));
        }
    }

    void toss() {
        cout << "Tossing the coin..." << endl;
        sleep(1);
        srand(time(0));
        int tossResult = rand() % 2;
        if (tossResult == 0) {
            cout << "Team A wins the toss and will bat first." << endl;
            battingTeam = teamA;
            bowlingTeam = teamB;
        } else {
            cout << "Team B wins the toss and will bat first." << endl;
            battingTeam = teamB;
            bowlingTeam = teamA;
        }
    }

    void startInning() {
        cout << "Starting Inning " << currentInning << endl;
        batsman = battingTeam->players[0];
        bowler = bowlingTeam->players[0];
    }

    void playInning() {
        for (int ball = 1; ball <= maxBalls; ball++) {
            cout << "Ball " << ball << ": ";
            int run = rand() % 7;
            batsman->ballsPlayed++;
            bowler->ballsBowled++;
            bowlingTeam->totalBallsBowled++;

            if (run == 0) {
                cout << batsman->name << " is OUT!" << endl;
                battingTeam->totalWickets++;
                if (battingTeam->totalWickets == 4) break;
                batsman = battingTeam->players[battingTeam->totalWickets];
            } else {
                batsman->runsScored += run;
                battingTeam->totalRuns += run;
                bowler->runsGiven += run;
                cout << batsman->name << " scores " << run << " run(s)." << endl;
            }
        }
    }

    void displayScore() {
        cout << "Scorecard for " << battingTeam->teamName << ": " << battingTeam->totalRuns << "/" << battingTeam->totalWickets << endl;
    }

    void swapTeams() {
        Team* temp = battingTeam;
        battingTeam = bowlingTeam;
        bowlingTeam = temp;
        currentInning++;
    }

    void matchSummary() {
        cout << "Match Summary:" << endl;
        cout << "Team A: " << teamA->totalRuns << "/" << teamA->totalWickets << endl;
        cout << "Team B: " << teamB->totalRuns << "/" << teamB->totalWickets << endl;
        if (teamA->totalRuns > teamB->totalRuns) {
            cout << "Team A wins!" << endl;
        } else if (teamB->totalRuns > teamA->totalRuns) {
            cout << "Team B wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
    }
};

int main() {
    Game game;
    game.teamA = new Team("Team A");
    game.teamB = new Team("Team B");

    game.welcome();
    game.displayAllPlayers();
    game.selectPlayers();
    game.toss();

    game.startInning();
    game.playInning();
    game.displayScore();
    game.swapTeams();

    game.startInning();
    game.playInning();
    game.displayScore();

    game.matchSummary();

    return 0;
}

