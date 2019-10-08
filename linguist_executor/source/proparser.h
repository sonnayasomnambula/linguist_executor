#ifndef PROPARSER_H
#define PROPARSER_H

#include <QDir>
#include <QSet>
#include <QMap>

class QString;
class QStringList;

class ProParser
{
public:
    bool load(const QString& name);
    QStringList tsFiles() const;

private:
    static QStringList joinBackslashed(const QStringList & source);
    static QString trimAndRemoveComment(const QString& s);
    void parse(const QString& line);
    void parseSubDirs(const QString& subdirs);
    void parseSubDirPath(QString subdir, QString path);
    void parseTranslations(QString translations);

    QDir mRoot;
    QSet<QString> mTsFiles;
    QMap<QString, QString> mSubDirs;

    friend class ProParserTest;
};

#endif // PROPARSER_H
