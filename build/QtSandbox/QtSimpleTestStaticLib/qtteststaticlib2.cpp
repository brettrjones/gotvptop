#include "qtteststaticlib2.h"
#include "qdebug.h"

QtTestStaticLib::QtTestStaticLib()
{
}

void QtTestStaticLib::printStuff()
{
    qWarning() << "printing static stuff ";
}


int QtTestStaticLib::getStaticValue()
{
    return 1;
}
