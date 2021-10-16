#include "recordmodal.h"
#include "ui_recordmodal.h"

#include <QDebug>

RecordModal::RecordModal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RecordModal)
{
    ui->setupUi(this);
}

RecordModal::~RecordModal()
{
    delete ui;
}

void RecordModal::setData(QString &data)
{
    QString jsonString = "<pre>" + data + "</pre>";
    ui->textBrowser->setText(jsonString);
}
