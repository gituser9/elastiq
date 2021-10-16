#include "connectdialog.h"
#include "ui_connectdialog.h"


ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    setModal(true);

    QSettings settings;
    QString host = settings.value("host").toString();
    QString port = settings.value("port").toString();
    QString index = settings.value("index").toString();

    if (port.isEmpty()) {
        port = "9200";
    }

    ui->leHost->setText(host);
    ui->lePort->setText(port);
    ui->leIndex->setText(index);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_buttonBox_accepted()
{
    QString host = ui->leHost->text();
    QString port = ui->lePort->text();
    QString index = ui->leIndex->text();

    QSettings settings;
    settings.setValue("host", host);
    settings.setValue("port", port);
    settings.setValue("index", index);

    QString newConnection = host + ":" + port + "/" + index;
    emit connectionUpdated(newConnection);
}

