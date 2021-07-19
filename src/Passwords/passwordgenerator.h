#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QString>
#include <ctime>

class PasswordGenerator
{
public:
    static QString generate();

private:
    static char randLetter();
    static char randNumber();
    static char randSpecSym();
};

#endif // PASSWORDGENERATOR_H
