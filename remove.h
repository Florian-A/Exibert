#ifndef REMOVEOBJECT_H
#define REMOVEOBJECT_H

#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <Qtimer>
#include <QCoreApplication>

class RemoveObject : public QObject
{
    Q_OBJECT
    public:
        explicit RemoveObject(QObject *parent = 0);

        QProcess *launch;
        QTimer *timer;

    public slots:

        void start();
        void shutdown();
};

#endif // REMOVEOBJECT_H
