#include "qttestsharedlib3.h"
#include "qdebug.h"

QtTestSharedLib::QtTestSharedLib()
{
}

void QtTestSharedLib::printStuff()
{
    qWarning() << "printing shared stuff ";
}



int QtTestSharedLib::getSharedValue()
{
    return 42;
}
