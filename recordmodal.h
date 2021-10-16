#ifndef RECORDMODAL_H
#define RECORDMODAL_H

#include <QDialog>

namespace Ui {
class RecordModal;
}

class RecordModal : public QDialog
{
    Q_OBJECT

public:
    explicit RecordModal(QWidget *parent = nullptr);
    ~RecordModal();

    void setData(QString &data);

private:
    Ui::RecordModal *ui;
};

#endif // RECORDMODAL_H
