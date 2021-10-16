#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

signals:
    void connectionUpdated(QString &);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
