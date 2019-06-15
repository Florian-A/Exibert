#ifndef NETWORKOBJECT_H
#define NETWORKOBJECT_H

#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFile>
#include <QUrl>
#include <QByteArray>

class NetworkObject : public QObject
{
    Q_OBJECT
    public:
        explicit NetworkObject(QObject *parent = 0);

        QNetworkReply *reply;
        bool networkGood;

    public slots:

        void test();
        void testReply(QNetworkReply *reply);

        void send();
        void done();

    private:

        QNetworkAccessManager manager;
        QFile file;
        QByteArray fileContent;
        QUrl url;
        QNetworkRequest request;
        QByteArray boundary;
        QByteArray data;
        QString cr;

    signals:

        void networkSended();
};

#endif // NETWORKOBJECT_H
