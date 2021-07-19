#include "passwordgenerator.h"

QString PasswordGenerator::generate()
{
    QString output = "";
    int length = 20 + rand() % 20;
    while(length--)
    {
        double probability;
        probability = rand() % 4;
        if(probability <= 1)
        {
            output.append(randLetter());
        }
        else if((probability > 1) && (probability <= 2))
        {
            output.append(randNumber());
        }
        else if(probability > 2)
        {
            output.append(randSpecSym());
        }
    }
    return output;
}

//=============================================================================

char PasswordGenerator::randLetter()
{
    int probability = rand() % 2;
    if(probability == 1)
    {
        return 65 + rand() % 26;
    }
    else
    {
        return 97 + rand() % 26;
    }

}

//=============================================================================

char PasswordGenerator::randNumber()
{
    return 48 + rand() % 10;
}

//=============================================================================

char PasswordGenerator::randSpecSym()
{
    char specSym[] = "[]{},.:;-_<>=?";
    return specSym[rand() % 14];
}
