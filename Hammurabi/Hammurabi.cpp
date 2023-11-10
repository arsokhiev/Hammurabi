#include <fstream>

#include "Hammurabi.h"
#include "HammurabiUtils.h"

HammurabiGame::HammurabiGame()
{
    People = START_PEOPLE;
    Acres = START_ACRES;
    Wheat = START_WHEAT;

    Round = 1;

    WheatHarvestedPerRound = 0;
    WheatHarvestedPerAcre = 0;

    WheatEatenByRats = 0;

    PeopleFaminedPerRound = 0;
    PeopleArrivedPerRound = 0;

    TotalFamined = 0;
    TotalPeople = 0;

    bWasPlague = false;
}

void HammurabiGame::BeginPlay()
{
    do
    {
        AcreCost = HammurabiUtils::RandBetween(17, 26);
        advisor_.ReportAnnualResults(Round, PeopleFaminedPerRound, PeopleArrivedPerRound, bWasPlague, People,
                                     WheatHarvestedPerRound, WheatHarvestedPerAcre, WheatEatenByRats, Wheat, Acres,
                                     AcreCost);

        if (Round > 1)
        {
            if (SaveAndQuit()) return;
        }

        if (!advisor_.AskForInstructions(&Wheat, &People, &Acres, &AcreCost, &PeopleFaminedPerRound,
                                    &WheatHarvestedPerAcre, &WheatHarvestedPerRound))
        {
            std::cout << phrases::IncorrectInputs;
            return;
        }

        WheatEatenByRats = static_cast<int>(std::ceil(HammurabiUtils::RandBetween(0.0f, 0.07f)))
            * (Wheat + WheatHarvestedPerRound);

        PeopleArrivedPerRound = std::clamp(PeopleFaminedPerRound / 2 + (5 - WheatHarvestedPerAcre)
                                           * (Wheat + WheatHarvestedPerRound - WheatEatenByRats) / 600 + 1, 0, 50);

        Wheat = Wheat + WheatHarvestedPerRound - WheatEatenByRats;
        People = People - PeopleFaminedPerRound + PeopleArrivedPerRound;

        bWasPlague = 0.15f > HammurabiUtils::RandBetween(0.0f, 1.0f);
        if (bWasPlague)
        {
            People /= 2;
        }

        TotalPeople += People;
        TotalFamined += PeopleFaminedPerRound;

        if (PeopleFaminedPerRound / (float)People > 0.45f)
        {
            std::cout << phrases::PeopleFamishingExit;
            return;
        }
    }
    while (++Round <= TOTAL_ROUNDS);

    advisor_.ReportAnnualResults(Round, PeopleFaminedPerRound, PeopleArrivedPerRound, bWasPlague, People,
                                 WheatHarvestedPerRound, WheatHarvestedPerAcre, WheatEatenByRats, Wheat, Acres,
                                 AcreCost);
    
    advisor_.ReportResultsOfReign(TotalFamined / static_cast<float>(TotalPeople), Acres / static_cast<float>(People));
}

void HammurabiGame::SaveToFile(std::ofstream& stream)
{
    stream << People << std::endl;
    stream << Acres << std::endl;
    stream << Wheat << std::endl;

    stream << Round << std::endl;

    stream << WheatHarvestedPerRound << std::endl;
    stream << WheatHarvestedPerAcre << std::endl;

    stream << WheatEatenByRats << std::endl;

    stream << PeopleFaminedPerRound << std::endl;
    stream << PeopleArrivedPerRound << std::endl;
    
    stream << TotalFamined << std::endl;
    stream << TotalPeople << std::endl;

    stream << bWasPlague << std::endl;
}

HammurabiGame* HammurabiGame::LoadFromFile(std::ifstream& stream)
{
    HammurabiGame* NewGame = new HammurabiGame();

    stream >> NewGame->People;
    stream >> NewGame->Acres;
    stream >> NewGame->Wheat;

    stream >> NewGame->Round;

    stream >> NewGame->WheatHarvestedPerRound;
    stream >> NewGame->WheatHarvestedPerAcre;

    stream >> NewGame->WheatEatenByRats;

    stream >> NewGame->PeopleFaminedPerRound;
    stream >> NewGame->PeopleArrivedPerRound;
    
    stream >> NewGame->TotalFamined;
    stream >> NewGame->TotalPeople;

    stream >> NewGame->bWasPlague;

    return NewGame;
}

bool HammurabiGame::SaveAndQuit()
{
    while (true)
    {
        std::cout << phrases::SaveGame;
        const int result = HammurabiUtils::GetValidInput(
            [](int value) { return value == 1 || value == 2; }, 3, phrases::EnterOneOrTwo);

        if (result == 1)
        {
            std::ofstream file;
            file.open("save", std::ios::trunc);

            SaveToFile(file);
            std::cout << phrases::SavedSuccessfully;

            file.close();
            return true;
        }
        if (result == 2)
        {
            return false;
        }
    }
}
