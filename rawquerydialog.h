#ifndef RAWQUERYDIALOG_H
#define RAWQUERYDIALOG_H

#include <QDialog>

namespace Ui {
class RawQueryDialog;
}

class RawQueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RawQueryDialog(QWidget *parent = nullptr);
    ~RawQueryDialog();

signals:
    void applyRawQuery(QString &);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RawQueryDialog *ui;
};

#endif // RAWQUERYDIALOG_H
