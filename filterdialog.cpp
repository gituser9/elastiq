#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle(tr("Filters"));

    json = "{}";

    connect(ui->leSize, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leSource, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leFrom, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leMatchName, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leMatchValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leWildcardName, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leWildcardValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leMatchPhraseName, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leMatchPhraseValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leTermName, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leTermValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leSortKey, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leSortValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->leRangeName, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leRangeKey, &QLineEdit::textChanged, this, &FilterDialog::generateJson);
    connect(ui->leRangeValue, &QLineEdit::textChanged, this, &FilterDialog::generateJson);

    connect(ui->btnClearAll, &QPushButton::clicked, this, &FilterDialog::clearAll);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::generateJson()
{
    QJsonObject jsonObj;

    // size
    if (!ui->leSize->text().isEmpty()) {
        int sizeInt = ui->leSize->text().toInt(0);

        if (sizeInt != 0) {
            jsonObj["size"] = sizeInt;
        }
    }

    // from
    if (!ui->leFrom->text().isEmpty()) {
        int fromInt = ui->leFrom->text().toInt(0);

        if (fromInt != 0) {
            jsonObj["from"] = fromInt;
        }
    }

    // _source
    if (!ui->leSource->text().isEmpty()) {
        QStringList sources = ui->leSource->text().split(",");
        jsonObj["_source"] = QJsonArray::fromStringList(sources);
    }

    // match
    if (!ui->leMatchName->text().isEmpty()) {
        QJsonObject matchObj{
            {ui->leMatchName->text(), ui->leMatchValue->text()},
        };

        if (!jsonObj.contains("query")) {
            jsonObj["query"] = QJsonObject{
                {"match", matchObj},
            };
        } else {
            auto queryObject = jsonObj["query"].toObject();
            queryObject["match"] = matchObj;
            jsonObj["query"] = queryObject;
        }
    }

    // wildcard
    if (!ui->leWildcardName->text().isEmpty()) {
        QJsonObject matchObj{
            {ui->leWildcardName->text(), ui->leWildcardValue->text()},
        };

        if (!jsonObj.contains("query")) {
            jsonObj["query"] = QJsonObject{
                {"wildcard", matchObj},
            };
        } else {
            auto queryObject = jsonObj["query"].toObject();
            queryObject["wildcard"] = matchObj;
            jsonObj["query"] = queryObject;
        }
    }

    // term
    if (!ui->leTermName->text().isEmpty()) {
        QJsonObject termObj{
            {ui->leTermName->text(), ui->leTermValue->text()},
        };

        if (!jsonObj.contains("query")) {
            jsonObj["query"] = QJsonObject{
                {"term", termObj},
            };
        } else {
            auto queryObject = jsonObj["query"].toObject();
            queryObject["term"] = termObj;
            jsonObj["query"] = queryObject;
        }
    }

    // sort
    if (!ui->leSortKey->text().isEmpty()) {
        jsonObj["sort"] = QJsonObject{
            {
                ui->leSortKey->text(),
                QJsonObject{
                    {"order", ui->leSortValue->text()},
                },
            },
        };
    }

    // range
    if (!ui->leRangeName->text().isEmpty()) {
        jsonObj["range"] = QJsonObject{
            {
                ui->leRangeName->text(),
                QJsonObject{
                    {ui->leRangeValue->text(), ui->leRangeKey->text()},
                },
            },
        };
    }

    // match phrase
    if (!ui->leMatchPhraseName->text().isEmpty()) {
        QJsonObject matchObj{
            {ui->leMatchPhraseName->text(), ui->leMatchPhraseValue->text()},
        };

        if (!jsonObj.contains("query")) {
            jsonObj["query"] = QJsonObject{
                {"match_phrase", matchObj},
            };
        } else {
            auto queryObject = jsonObj["query"].toObject();
            queryObject["match_phrase"] = matchObj;
            jsonObj["query"] = queryObject;
        }
    }

    json = QJsonDocument(jsonObj).toJson(QJsonDocument::JsonFormat::Indented);

    ui->tbPreview->setText("<pre>" + json + "</pre>");
}

void FilterDialog::clearAll()
{
    json = "{}";

    ui->leSize->setText("");
    ui->leSource->setText("");
    ui->leFrom->setText("");

    ui->leMatchName->setText("");
    ui->leMatchValue->setText("");

    ui->leWildcardName->setText("");
    ui->leWildcardValue->setText("");

    ui->leMatchPhraseName->setText("");
    ui->leMatchPhraseValue->setText("");

    ui->leTermName->setText("");
    ui->leTermValue->setText("");

    ui->leSortKey->setText("");
    ui->leSortValue->setText("");

    ui->leRangeName->setText("");
    ui->leRangeKey->setText("");
    ui->leRangeValue->setText("");

    ui->tbPreview->setText("<pre>" + json + "</pre>");
}

void FilterDialog::on_buttonBox_accepted()
{
    emit applyFilters(json);
}

