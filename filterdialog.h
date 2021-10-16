#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

signals:
    void applyFilters(QString &);

private slots:
    void on_buttonBox_accepted();
    void generateJson();
    void clearAll();

private:
    Ui::FilterDialog *ui;
    QString json;
};

#endif // FILTERDIALOG_H
