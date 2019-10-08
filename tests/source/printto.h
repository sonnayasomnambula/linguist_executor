#ifndef PRINTTO_H
#define PRINTTO_H

/** @file */

#include <ostream>

class QString;
class QStringList;

/**
 * @name PrintTo
 * Customize googletest debug output
 * @see https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#teaching-googletest-how-to-print-your-values
 */
///@{
void PrintTo(const QString& s, std::ostream* os);
void PrintTo(const QStringList& s, std::ostream* os);
///@}

#endif // PRINTTO_H
