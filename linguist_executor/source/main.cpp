#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QFileInfo>

#include "proparser.h"
#include "tsselectdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const auto args = QCoreApplication::arguments();
    if (args.size() < 3)
    {
        qWarning() << QString(R"(
Qt Linguist executor utility.
usage: "%1 %{CurrentProject:FilePath} %{CurrentProject:QT_INSTALL_BINS}")")
                      .arg(QFileInfo(args[0]).fileName());
        return -1;
    }

    const auto& projectFile = args[1];
    ProParser pro;
    if (!pro.load(projectFile))
    {
        qWarning() << "Cannot load" << projectFile;
        return -1;
    }

    TsSelectDialog d;
    d.setList(pro.tsFiles());
    if (d.exec())
    {
        const auto& linguist = args[2] + QDir::separator() + "linguist";
        QProcess::execute(linguist, {d.selectedLine()});
    }

    return 0;
}
