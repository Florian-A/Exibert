#include <global.h>
#include <camera.h>

CameraObject::CameraObject(QObject *parent) : QObject(parent)
{
    // Création de l'objet //
    camera = new QCamera();
    imageCapture = new QCameraImageCapture(camera);
    QVideoWidget *widget = new QVideoWidget();

    // Paramétrage de la camera //
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(widget);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    QImageEncoderSettings imageSettings;
    imageSettings.setCodec("image/jpeg");
    imageSettings.setQuality(QMultimedia::VeryHighQuality);

    // Enregistrement des paramètres de la camera //
    imageCapture->setEncodingSettings(imageSettings);
}


void CameraObject::start()
{
    // Démarrage de la caméra //
    camera->start();

    // Démarrage de la capture avec son emplacement //
    imageCapture->capture(GLOBAL_cameraPath);
}

void CameraObject::stop()
{
    QThread::msleep(500);
    // Déchargement de l'object camera pour éviter une fuite mémoire //
    camera->unload();

    // Arrêt de la caméra //
    camera->stop();

    // Envoi du signal //
    emit cameraStoped();
}
