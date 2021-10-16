#include "datamodel.h"

DataModel::DataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("#");
        case 1:
            return QString("Index");
        case 2:
            return QString("Type");
        case 3:
            return QString("Id");
        }
    }

    return QVariant();
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return elasticData.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return 4;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    ElasticRecord record = elasticData[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return index.row() + 1;
        case 1:
            return record.index;
        case 2:
            return record.type;
        case 3:
            return record.id;
        }
    }

    return QVariant();
}

void DataModel::setResponseData(const QByteArray &data)
{
    // распарсить дату в жсон
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject responseObject = document.object();
    QJsonArray jsonArray = responseObject["hits"].toObject()["hits"].toArray();

    // данные жсон проставить в структуры
    elasticData.clear();
    elasticData.reserve(jsonArray.count());

    for (auto &&item : jsonArray) {
        QJsonObject itemObj = item.toObject();

        elasticData.emplace_back(ElasticRecord(itemObj));
    }

    beginResetModel();
    endResetModel();
}

void DataModel::clearData()
{
    beginResetModel();
    elasticData.clear();
    elasticData.resize(0);
    endResetModel();
}

void DataModel::onTableRowClicked(const QModelIndex &index)
{
    ElasticRecord record = elasticData[index.row()];

    emit tableRowDoubleClicked(record);
}
