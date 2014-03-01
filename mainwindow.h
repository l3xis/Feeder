#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QtWidgets/QMessageBox>
#include <QStringListModel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QSettings>
#include <QVariant>
#include <QTreeWidgetItem>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QModelIndex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>

#include <o2/src/o2.h>
#include <o2/src/o2settingsstore.h>
#include <o2/src/o2globals.h>
#include <o2/src/o2requestor.h>

#include <subscribedialog.h>
#define SUBSCRIPTION 100

const char CLIENT_SECRET[] = "W60IW73DYSUIISZX4OUP";
const char CLIENT_ID[] = "sandbox";
const char TOKEN_URL[] = "https://sandbox.feedly.com/v3/auth/token";
const char REQUEST_URL[] = "http://sandbox.feedly.com/v3/auth/auth";
const char SCOPE[] = "https://cloud.feedly.com/subscriptions";
const char REFRESH_TOKEN_URL[] = "http://sandbox.feedly.com/v3/auth/token";
const QString SUBSCRIPTIONS_URL = "http://sandbox.feedly.com/v3/subscriptions";
const QString CATEGORIES_URL = "http://sandbox.feedly.com/v3/categories";
const QString STREAMS_CONTENTS_URL = "http://sandbox.feedly.com/v3/streams/contents?streamId=";
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_Qt_triggered();
    void onTreeViewClicked(const QModelIndex &);
    void onLinkedChanged();
    void onLinkingFailed();
    void onLinkingSucceeded();
    void onOpenBrowser(const QUrl &url);
    void onTokenChanged();
    void onReqFinished(int id, QNetworkReply::NetworkError error, QByteArray data);
    void on_actionSubscribe_to_a_feed_triggered();
    bool on_subscibe();
    void reqCategories();
    void reqSubscriptions();
    void handleCategoryResp(QByteArray data);
    void handleSubscriptionsResp(QByteArray data);
    void handleContentsResp(QByteArray data);
private:

    enum ReqStatus {
        Auth,Preference,Categories,Subscriptions,Tags,Contents
    };

    Ui::MainWindow *ui;
    QSettings *setting;
    O2SettingsStore *store;
    O2 *o2 ;
    O2Requestor *o2req;
    QNetworkRequest request;
    QNetworkAccessManager* nam;
    ReqStatus reqStatus;
    QString userId;
    QString plan;
    SubscribeDialog *subDialog;

    QList<QTreeWidgetItem *> items;
    QStringListModel *listModel;
    QStandardItemModel *treeModel;

    QMap<QString,QStandardItem*> categorieMap;
    QMap<QString,QStringList> subscriptionMap;
};

#endif // MAINWINDOW_H