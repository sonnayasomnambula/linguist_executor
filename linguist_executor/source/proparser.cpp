#include "proparser.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>

bool ProParser::load(const QString& name)
{
    QFile pro(name);
    if (!pro.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << QObject::tr("Cannot open '%1'").arg(name);
        return false;
    }

    mRoot.setPath(QDir::cleanPath(QFileInfo(name).dir().absolutePath()));

    QTextStream in(&pro);
    QStringList lines = joinBackslashed(in.readAll().split("\n"));

    for (auto s : lines)
    {
        parse(s);
    }

    for (const QString& subdir: mSubDirs.keys())
    {
        ProParser parser;
        if (parser.load(mSubDirs.value(subdir)))
        {
            mTsFiles.unite(QSet<QString>::fromList(parser.tsFiles()));
        }
    }

    if (mTsFiles.isEmpty())
        qWarning() << "no translations found in" << name;

    return true;
}

QStringList ProParser::tsFiles() const
{
    return mTsFiles.toList();
}

QStringList ProParser::joinBackslashed(const QStringList& source)
{
    QStringList result;
    QString longLine;
    for (const QString& s: source)
    {
        const QString trimmed = trimAndRemoveComment(s);
        if (trimmed.endsWith("\\"))
        {
            longLine += trimmed;
            longLine.remove(longLine.size() - 1, 1);
        }
        else
        {
            longLine.append(trimmed);
            result.append(longLine.trimmed());
            longLine.clear();
        }
    }

    if (!longLine.isEmpty())
    {
        result.append(longLine);
        longLine.clear();
    }

    return result;
}

QString ProParser::trimAndRemoveComment(const QString& s)
{
    QString result = s.trimmed();
    const int i = result.lastIndexOf('#');
    if (i >= 0)
        result.remove(i, result.size() - i);
    return result.trimmed();
}

void ProParser::parse(const QString& line)
{
    QStringList kval = line.split(line.contains("+=") ? "+=" : "=");
    if (kval.size() == 2)
    {
        const QString& key = kval.first().trimmed();
        const QString& value = kval.last().trimmed();

        if (key == "SUBDIRS")
        {
            parseSubDirs(value);
        }

        if (key.endsWith(".subdir"))
        {
            parseSubDirPath(key, value);
        }

        if (key == "TRANSLATIONS")
        {
            parseTranslations(value);
        }
    }
}

void ProParser::parseSubDirs(const QString& subdirs)
{
    for (const QString& s: subdirs.split(" "))
    {
        const QString subdir = s.trimmed();
        mSubDirs[subdir] = mRoot.absoluteFilePath(subdir) + QDir::separator() + subdir + ".pro";
    }
}

void ProParser::parseSubDirPath(QString subdir, QString path)
{
    subdir.remove(".subdir");
    path.replace("$$PWD", mRoot.absolutePath());
    mSubDirs[subdir] = path + QDir::separator() + subdir + ".pro";
}

void ProParser::parseTranslations(QString translations)
{
    for (QString path: translations.split(" "))
    {
        path = path.trimmed();
        if (!path.startsWith("$$PWD"))
            path.prepend(QString("$$PWD") + QDir::separator());
        path.replace("$$PWD", mRoot.absolutePath());
        mTsFiles.insert(QDir::cleanPath(path));
    }

}
