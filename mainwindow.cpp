#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _progressBar = new QProgressBar(this);
    _progressBar->setHidden(true);
    _progressBar->setRange(0, 0);

    _abortButton = new QPushButton(this);
    _abortButton->setHidden(true);
    _abortButton->setText(tr("Cancel"));

    _filterDialog = new FilterDialog(this);
    _rawQueryDialog = new RawQueryDialog(this);
    _connectDialog = new ConnectDialog(this);
    _recordModal = new RecordModal(this);

    _dataModel = new DataModel(this);
    _httpService = new HttpService(this);

    ui->tableView->setModel(_dataModel);
    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(3, 500);

    // filter dialog
    connect(_filterDialog, &FilterDialog::applyFilters, this, &MainWindow::sendRequest);
    connect(_rawQueryDialog, &RawQueryDialog::applyRawQuery, this, &MainWindow::sendRequest);

    connect(_connectDialog, &ConnectDialog::connectionUpdated, this, &MainWindow::onConnectioUpdate);

    // http_service
    connect(_httpService, &HttpService::didGetByFilters, this, &MainWindow::onDidgetByFilters);
    connect(_httpService, &HttpService::didGetById, this, &MainWindow::onDidgetById);

    //abort button
    connect(_abortButton, &QPushButton::clicked, _httpService, &HttpService::abortReply);
    connect(_abortButton, &QPushButton::clicked, this, &MainWindow::hideStatusBarWidgets);

    // table
    connect(ui->tableView, &QTableView::doubleClicked, _dataModel, &DataModel::onTableRowClicked);

    // model
    connect(_dataModel,
            &DataModel::tableRowDoubleClicked,
            this,
            &MainWindow::onTebleRowDoubleClicked);

    // read settings
    QString host = _settings.value("host").toString();
    QString port = _settings.value("port").toString();
    QString index = _settings.value("index").toString();

    // set connection string to http_service
    _httpService->setRootUrl(host + ":" + port + "/" + index);

    // setup status bar
    ui->statusbar->showMessage("connected to: " + _httpService->rootUrl());
    ui->statusbar->addPermanentWidget(_abortButton);
    ui->statusbar->addPermanentWidget(_progressBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    _connectDialog->show();
}

void MainWindow::on_actionGet_by_id_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(
        this,
        tr("Get by id"),
        tr("Id:"),
        QLineEdit::Normal,
        "",
        &ok
    );

    if (ok && !text.isEmpty()) {
        _httpService->getById(text);
    }
}

void MainWindow::on_actionFilter_triggered()
{
    _filterDialog->show();
}

void MainWindow::sendRequest(QString json)
{
    _abortButton->setHidden(false);
    _progressBar->setHidden(false);
    _httpService->getByFilters(json);
}

void MainWindow::on_actionClear_triggered()
{
    _dataModel->clearData();
}

void MainWindow::on_actionRawQuery_triggered()
{
    _rawQueryDialog->show();
}

void MainWindow::onDidgetByFilters(QByteArray &data)
{
    _dataModel->setResponseData(data);

    hideStatusBarWidgets();
}

void MainWindow::onDidgetById(QByteArray &data)
{
    QString jsonString = QJsonDocument::fromJson(data).toJson(QJsonDocument::Indented);

    auto recordModal = new RecordModal();
    recordModal->setData(jsonString);
    recordModal->show();
}

void MainWindow::onConnectioUpdate(QString &newConnection)
{
    _httpService->setRootUrl(newConnection);
    ui->statusbar->showMessage("connected to: " + _httpService->rootUrl());
}

void MainWindow::onTebleRowDoubleClicked(ElasticRecord &record)
{
    _recordModal->setData(record.source);
    _recordModal->setWindowTitle(record.id);
    _recordModal->show();
}

void MainWindow::hideStatusBarWidgets()
{
    _abortButton->setHidden(true);
    _progressBar->setHidden(true);
}
