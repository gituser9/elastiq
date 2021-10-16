#include "rawquerydialog.h"
#include "ui_rawquerydialog.h"

RawQueryDialog::RawQueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RawQueryDialog)
{
    ui->setupUi(this);
}

RawQueryDialog::~RawQueryDialog()
{
    delete ui;
}

void RawQueryDialog::on_buttonBox_accepted()
{
    QString json = ui->textBrowser->toPlainText();

    if (json.isEmpty()) {
        return;
    }

    emit applyRawQuery(json);
}
