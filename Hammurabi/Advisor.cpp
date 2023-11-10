#include "Advisor.h"
#include "HammurabiUtils.h"

bool Advisor::AskForInstructions(int* wheat, int* people, int* acres, int* acreCost, int* peopleFaminedPerRound,
                                 int* wheatHarvestedPerAcre, int* wheatHarvestedPerRound)
{
    std::cout << phrases::Greetings;

    if (!ByOrSellAcres(wheat, acres, acreCost)) return false;
    if (!WheatConsumption(wheat, people, peopleFaminedPerRound)) return false;
    if (!SowWithWheat(wheat, acres, people, wheatHarvestedPerAcre, wheatHarvestedPerRound)) return false;

    return true;
}

bool Advisor::ByOrSellAcres(int* wheat, int* acres, int* acreCost)
{
    std::cout << phrases::AcresPurchase;
    int PlayerInput = HammurabiUtils::GetValidInput(
        [wheat, acreCost](const int value)
        {
            return value >= 0 && value <= *wheat / *acreCost;
        },
        3, phrases::NoWheatToBuyAcres);
    
    if (PlayerInput == -1) return false;
    
    if (PlayerInput > 0)
    {
        *acres += PlayerInput;
        *wheat -= PlayerInput * *acreCost;
    }
    else if (PlayerInput == 0)
    {
        std::cout << phrases::AcresSale;
        PlayerInput = HammurabiUtils::GetValidInput(
            [acres](const int value)
            {
                return value >= 0 && value <= *acres;
            },
            3, phrases::NoAcresToSell);

        if (PlayerInput == -1) return false;
        
        if (PlayerInput > 0)
        {
            *acres -= PlayerInput;
            *wheat += PlayerInput * *acreCost;
        }
    }

    return true;
}

bool Advisor::WheatConsumption(int* wheat, int* people, int* peopleFaminedPerRound)
{
    std::cout << phrases::UseWheatForFood;
    int PlayerInput = HammurabiUtils::GetValidInput(
        [wheat](int value)
        {
            return value >= 0 && value <= *wheat;
        },
        3, phrases::NoWheatToEat);

    if (PlayerInput == -1) return false;
    
    if (PlayerInput > 0)
    {
        *peopleFaminedPerRound = *people - static_cast<int>(std::ceil(PlayerInput / 20.0f));
        *wheat -= PlayerInput;
    }

    return true;
}

bool Advisor::SowWithWheat(int* wheat, int* acres, int* people, int* wheatHarvestedPerAcre, int* wheatHarvestedPerRound)
{
    std::cout << phrases::SowAcres;

    bool isPositive = false;
    bool isEnoughAcres = false;
    bool isEnoughWheat = false;
    bool isEnoughCitizens = false;

    int PlayerInput = HammurabiUtils::GetValidInput(
        [wheat, acres, people, &isPositive, &isEnoughAcres, &isEnoughCitizens, &isEnoughWheat](int value)
        {
            isEnoughAcres = value <= *acres;
            isEnoughCitizens = value <= *people * 10;
            isEnoughWheat = value <= *wheat * 2;
            isPositive = value >= 0;

            return isPositive && isEnoughAcres && isEnoughCitizens && isEnoughWheat;
        },
        3, isPositive
               ? isEnoughAcres
                     ? isEnoughWheat
                           ? isEnoughCitizens
                                 ? "\n"
                                 : phrases::NoEnoughCitizensToSow
                           : phrases::NoEnoughWheatToSow
                     : phrases::NoEnoughAcresToSow
               : phrases::EnteredNumIsNotValid);

    if (PlayerInput == -1) return false;

    if (PlayerInput > 0)
    {
        *wheat -= static_cast<int>(std::ceil(PlayerInput / 2.0f));
        *wheatHarvestedPerAcre = HammurabiUtils::RandBetween(1, 6);
        *wheatHarvestedPerRound = *wheatHarvestedPerAcre * PlayerInput;
    }
}

void Advisor::ReportAnnualResults(int round, int peopleFamined, int peopleArrived, bool bWasPlague, int People,
                                  int wheatHarvestedPerRound, int wheatHarvestedPerAcre, int wheatEatenByRats,
                                  int wheat, int acres, int acreCost)
{
    std::cout << "Мой повелитель, соизволь поведать тебе:\n";

    if (round != 1)
    {
        std::cout << "В " << round << " году твоего высочайшего правления:\n";

        if (peopleFamined)
        {
            std::cout << peopleFamined << " человек умерли с голоду;\n";
        }
        if (peopleArrived)
        {
            std::cout << peopleArrived << " человек прибыли в наш великий город;\n";
        }
        if (bWasPlague)
        {
            std::cout << "Чума уничтожила половину населения;\n";
        }

        std::cout << "Мы собрали " << wheatHarvestedPerRound << " бушелей пшеницы, по " << wheatHarvestedPerAcre <<
            " бушеля с акра;\n";

        if (wheatEatenByRats)
        {
            std::cout << "Крысы истребили " << wheatEatenByRats << " бушелей пшеницы, оставив " << wheat <<
                " бушеля в амбарах;\n";
        }
        std::cout << "1 акр земли стоит сейчас " << acreCost << " бушелей;\n\n";
    }
    std::cout << "В ваших амбарах " << wheat << " бушелей пшеницы;\n"
        << "В городе проживает " << People << " людей на " << acres << " земли\n\n";
}

void Advisor::ReportResultsOfReign(float averageFaminedPercent, float acresPerPerson)
{
    if (averageFaminedPercent > 0.33f && acresPerPerson < 7.0f)
    {
        std::cout << phrases::AwfulEnd;
        return;
    }
    if (averageFaminedPercent > 0.1f && acresPerPerson < 9.0f)
    {
        std::cout << phrases::SatisfactorilyEnd;
        return;
    }
    if (averageFaminedPercent > 0.03f && acresPerPerson < 10.0f)
    {
        std::cout << phrases::FineEnd;
        return;
    }
    std::cout << phrases::PerfectEnd;
}
