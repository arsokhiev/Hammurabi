#pragma once
#include "Advisor.h"

class HammurabiGame
{
public:
    HammurabiGame();
    
    void BeginPlay();

    void SaveToFile(std::ofstream& stream);
    static HammurabiGame* LoadFromFile(std::ifstream& stream);

private:
    // basic stats
    int People;
    int Acres;
    int Wheat;

    int Round;

    // harvesting wheat
    int WheatHarvestedPerRound;
    int WheatHarvestedPerAcre;

    // wheat consumption
    int WheatEatenByRats;

    // population change
    int PeopleFaminedPerRound;
    int PeopleArrivedPerRound;

    int TotalFamined;
    int TotalPeople;

    int bWasPlague;

    int AcreCost;

    Advisor advisor_;

    bool SaveAndQuit();

public:
    const int START_PEOPLE = 100;
    const int START_ACRES = 1000;
    const int START_WHEAT = 2800;
    const int TOTAL_ROUNDS = 10;
};
