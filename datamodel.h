#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "app_struct.h"
#include "recordmodal.h"

class DataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DataModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setResponseData(const QByteArray &data);
    void clearData();

signals:
    void tableRowDoubleClicked(ElasticRecord &);

public slots:
    void onTableRowClicked(const QModelIndex &index);

private:
    std::vector<ElasticRecord> elasticData;
};

#endif // DATAMODEL_H
