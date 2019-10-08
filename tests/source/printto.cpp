#include "printto.h"

#include <QString>
#include <QStringList>

void PrintTo(const QString& s, std::ostream* os)
{
    *os << "\"" << qPrintable(s) << "\"";
}

void PrintTo(const QStringList& s, std::ostream* os)
{
    *os << "{\"" << qPrintable(s.join("\", \"")) << "\"}";
}
