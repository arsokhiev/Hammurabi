#pragma once
#include <string>

class Advisor
{
public:
    Advisor() = default;

    bool AskForInstructions(int* wheat, int* people, int* acres, int* acreCost, int* peopleFaminedPerRound,
                            int* wheatHarvestedPerAcre, int* wheatHarvestedPerRound);

    void ReportAnnualResults(int round, int peopleFamined, int peopleArrived, bool bWasPlague, int People,
                             int wheatHarvestedPerRound, int wheatHarvestedPerAcre, int wheatEatenByRats,
                             int wheat, int acres, int acreCost);

    void ReportResultsOfReign(float averageFaminedPercent, float acresPerPerson);
    
private:
    bool ByOrSellAcres(int* wheat, int* acres, int* acreCost);
    bool WheatConsumption(int* wheat, int* people, int* peopleFaminedPerRound);
    bool SowWithWheat(int* wheat, int* acres, int* people, int* wheatHarvestedPerAcre, int* wheatHarvestedPerRound);
};

namespace phrases
{
    // reign results
    inline std::string AwfulEnd = "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. "
        "Теперь вы вынуждены влачить жалкое существование в изгнании\n";
    inline std::string SatisfactorilyEnd = "Вы правили железной рукой, подобно Нерону и Ивану Грозному. "
        "Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем\n";
    inline std::string FineEnd = "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, "
        "но многие хотели бы увидеть вас во главе города снова\n";
    inline std::string PerfectEnd = "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше\n";


    inline std::string StartOrLoad = "Hammurabi\n 1 - Начать игру\n 2 - Продолжить предыдущую сессию\n 3 - Выйти\n\n";
    
    // working with saves
    inline std::string LoadGame = "Продолжить предыдущую игру?\n 1 - Продолжить предыдущую\n 2 - Начать заново\n\n";
    inline std::string SaveGame = "Вы хотите сохранить игру?\n 1 - Да\n 2 - Нет\n\n";
    inline std::string EnterOneOrTwo = "Нужно ввести 1 или 2.\n";
    inline std::string EnterOneOrTwoOrThree = "Нужно ввести 1, 2 или 3\n";
    inline std::string SavedSuccessfully = "Сохранено успешно!\n\n";

    // resource manage
    inline std::string Greetings = "Что пожелаешь, повелитель?\n";
    inline std::string AcresPurchase = "Сколько акров земли повелеваешь купить? ";
    inline std::string AcresSale = "Сколько акров земли повелеваешь продать? ";
    inline std::string UseWheatForFood = "Сколько бушелей пшеницы повелеваешь съесть? ";
    inline std::string SowAcres = "Сколько акров земли повелеваешь засеять? ";
    
    // error messages
    inline std::string IncorrectInputs = "\nВы вводите некорректные значения. Игра будет завершена\n";
    inline std::string PeopleFamishingExit = "\nОт голода умерла половина горожан. Игра будет завершена\n";
    
    inline std::string EnteredNumIsNotValid = "\nИзвините, я вас не понял... Сколько? ";

    inline std::string NoWheatToBuyAcres = "\nУ нас недостаточно пшеницы для покупки земли";
    inline std::string NoAcresToSell = "\nМы не можем продать земли больше чем весь город";
    inline std::string NoWheatToEat = "\nВ запасах нет столько пшеницы";

    inline std::string NoEnoughAcresToSow = "\nУ нас нет столько земли, для посевов";
    inline std::string NoEnoughCitizensToSow = "\nУ нас не хватит рук, для посевов";
    inline std::string NoEnoughWheatToSow = "\nУ нас нет столько свободной пшеницы, для посевов";
}
