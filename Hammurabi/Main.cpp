#include <fstream>
#include <windows.h>
#include "Hammurabi.h"
#include "HammurabiUtils.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    HammurabiGame* HammurabiGameSession = nullptr;

    while (true)
    {
        if (HammurabiGameSession != nullptr) delete HammurabiGameSession;

        std::cout << phrases::StartOrLoad;

        int PlayerInput = HammurabiUtils::GetValidInput([](const int value)
        {
            return value >= 1 && value <= 3;
        }, 3, phrases::EnterOneOrTwoOrThree);

        if (PlayerInput == -1) PlayerInput = 3;

        switch (PlayerInput)
        {
        case 1:
            HammurabiGameSession = new HammurabiGame();
            HammurabiGameSession->BeginPlay();
            break;
        case 2:
            {
                std::ifstream file;
                file.open("save");

                if (!file.is_open())
                {
                    std::cout << "No save file found." << std::endl;
                    continue;
                }
                HammurabiGameSession = HammurabiGame::LoadFromFile(file);
                if (HammurabiGameSession == nullptr)
                {
                    std::cout << "Save file is corrupt." << std::endl;
                    continue;
                }

                file.close();

                HammurabiGameSession->BeginPlay();
                break;
            }
        case 3:
            return 0;
        }
    }
}
