#ifndef CAMERA_H
#define CAMERA_H

#include <QMultimedia>
#include <QCameraImageCapture>
#include <QCamera>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QThread>

class CameraObject : public QObject
{
    Q_OBJECT
    public:
        explicit CameraObject(QObject *parent = 0);

        QCameraImageCapture* imageCapture;
        QCamera* camera;

    public slots:

        void start();
        void stop();

    signals:

        void cameraStoped();
};

#endif // CAMERA_H
