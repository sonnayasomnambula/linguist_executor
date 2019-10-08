#include "tsselectdialog.h"
#include "ui_tsselectdialog.h"

#include <QItemSelectionModel>
#include <QPushButton>

TsSelectDialog::TsSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TsSelectDialog)
{
    ui->setupUi(this);

    connect(ui->list, &QListWidget::itemDoubleClicked,
            this, &TsSelectDialog::accept);

    connect(ui->list->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TsSelectDialog::onSelectionChange);

    onSelectionChange();
}

TsSelectDialog::~TsSelectDialog() = default;

void TsSelectDialog::setList(const QStringList& list)
{
    ui->list->clear();
    ui->list->addItems(list);
    onSelectionChange();
}

QString TsSelectDialog::selectedLine()
{
    const auto& selection = ui->list->selectedItems();
    return selection.isEmpty() ? "" : selection.first()->text();
}

void TsSelectDialog::onSelectionChange()
{
    QPushButton* bOk = ui->buttonBox->button(QDialogButtonBox::Ok);
    Q_ASSERT(bOk);
    bOk->setEnabled(!ui->list->selectedItems().isEmpty());
}
