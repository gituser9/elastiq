#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>

#include "connectdialog.h"
#include "filterdialog.h"
#include "rawquerydialog.h"
#include "recordmodal.h"

#include "datamodel.h"
#include "httpservice.h"


QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // panel triggers
    void on_actionConnect_triggered();
    void on_actionGet_by_id_triggered();
    void on_actionFilter_triggered();
    void on_actionClear_triggered();
    void on_actionRawQuery_triggered();

    void sendRequest(QString json);

    // http response slots
    void onDidgetByFilters(QByteArray &data);
    void onDidgetById(QByteArray &data);

    void onConnectioUpdate(QString &newConnection);

    void onTebleRowDoubleClicked(ElasticRecord &record);

private:
    Ui::MainWindow *ui;
    QSettings _settings;
    QProgressBar *_progressBar;
    QPushButton *_abortButton;

    // dialogs
    ConnectDialog *_connectDialog;
    FilterDialog *_filterDialog;
    RawQueryDialog *_rawQueryDialog;
    RecordModal *_recordModal;

    // data services
    DataModel *_dataModel;
    HttpService *_httpService;

private slots:
    void hideStatusBarWidgets();
};

#endif // MAINWINDOW_H
