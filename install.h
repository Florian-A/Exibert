#ifndef INSTALLOBJECT_H
#define INSTALLOBJECT_H

#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <Qtimer>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QThread>


class InstallObject : public QObject
{
    Q_OBJECT
    public:
        explicit InstallObject(QObject *parent = 0);

        QTimer *timer;

    public slots:

        void checking();
        void start();
        void shutdown();
};

#endif // INSTALLOBJECT_H
