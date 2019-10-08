#ifndef TSSELECTDIALOG_H
#define TSSELECTDIALOG_H

#include <QDialog>
#include <QScopedPointer>

namespace Ui {
class TsSelectDialog;
}

class QDir;

class TsSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TsSelectDialog(QWidget *parent = nullptr);
    ~TsSelectDialog();

    void setList(const QStringList& list);
    QString selectedLine();

private:
    void onSelectionChange();

    QScopedPointer<Ui::TsSelectDialog> ui;
};

#endif // TSSELECTDIALOG_H
