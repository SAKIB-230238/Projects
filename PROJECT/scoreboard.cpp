#include <iostream>
#include <vector>
#include <string>

class Team
{
    std::string teamName;
    std::vector<std::string> playerNames;
    std::vector<int> playerRuns;
    std::vector<int> playerStatus; // 0: not out, 1: out
    int extraRuns;
    int playerCount;

public:
    Team();
    void init();
    void addRun(int playerNum, int runs);
    void setOut(int playerNum);
    void showScore() const;
    int getTotalRuns() const;
};

Team::Team() : extraRuns(0), playerCount(0) {}

void Team::init()
{
    std::cout << "Enter Team Name: ";
    std::cin >> teamName;

    std::cout << "Number of Players: ";
    std::cin >> playerCount;

    playerNames.resize(playerCount);
    playerRuns.resize(playerCount, 0);
    playerStatus.resize(playerCount, 0);

    std::cout << "Enter Names of the Players:\n";
    for (int i = 0; i < playerCount; ++i)
    {
        std::cout << "Player " << (i + 1) << ": ";
        std::cin >> playerNames[i];
    }
}

void Team::addRun(int playerNum, int runs)
{
    playerRuns[playerNum] += runs;
}

void Team::setOut(int playerNum)
{
    playerStatus[playerNum] = 1; // Mark player as out
}

void Team::showScore() const
{
    std::cout << "\nTeam: " << teamName << "\n";
    std::cout << "Player\tStatus\tRuns\n";
    for (int i = 0; i < playerCount; ++i)
    {
        std::cout << playerNames[i] << "\t"
                  << (playerStatus[i] == 1 ? "Out" : "Not Out") << "\t"
                  << playerRuns[i] << "\n";
    }
    std::cout << "Total Runs: " << getTotalRuns() << "\n";
}

int Team::getTotalRuns() const
{
    int total = extraRuns;
    for (int runs : playerRuns)
    {
        total += runs;
    }
    return total;
}

class ScoreManager
{
    Team team;
    int ballsPlayed;
    int wickets;

public:
    ScoreManager();
    void play();
};

ScoreManager::ScoreManager() : ballsPlayed(0), wickets(0)
{
    team.init();
}

void ScoreManager::play()
{
    int choice, playerNum, runs;
    while (true)
    {
        team.showScore();
        std::cout << "\nOptions:\n"
                  << "1. Add Runs\n"
                  << "2. Set Out\n"
                  << "3. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter Player Number (1-" << team.getTotalRuns() << "): ";
            std::cin >> playerNum;
            std::cout << "Enter Runs: ";
            std::cin >> runs;
            team.addRun(playerNum - 1, runs);
            ballsPlayed++;
            break;

        case 2:
            std::cout << "Enter Player Number (1-" << team.getTotalRuns() << "): ";
            std::cin >> playerNum;
            team.setOut(playerNum - 1);
            wickets++;
            break;

        case 3:
            return;

        default:
            std::cout << "Invalid choice! Try again.\n";
            break;
        }
    }
}

int main()
{
    ScoreManager scoreManager;
    scoreManager.play();
    return 0;
}