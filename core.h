#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <global.h>
#include <camera.h>
#include <network.h>
#include <painter.h>
#include <remove.h>
#include <install.h>

#include <QString>
#include <QDateTime>

class CoreObject : public QObject
{
    Q_OBJECT
    public:
        explicit CoreObject(QObject *parent = 0);

        QTimer *timer;
        QDateTime * timestamp;

        NetworkObject * network;
        PainterObject * painter;
        CameraObject * camera;
        RemoveObject * remove;
        InstallObject * install;

        ~CoreObject();

    private:

        bool loopFirst;
        int nbWantShoot;
        int nbRealShoot;

    public slots:

        void loop();
        void loopModify(int loopTimer);

        void cameraShoot(int nbShoot);
        void cameraSterilization();
        void cameraStart();
        void cameraStop();

        void painterStart();
        void networkStart();

};

#endif // COREOBJECT_H
