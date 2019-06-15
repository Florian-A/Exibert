#include <core.h>

CoreObject::CoreObject(QObject *parent) : QObject(parent)
{
    // Définition des objets //
    timer = new QTimer(this);
    timestamp = new QDateTime();
    install = new InstallObject();
    remove = new RemoveObject();
    camera = new CameraObject();
    network = new NetworkObject();
    painter = new PainterObject();

    // Test si le programme est installé //
    //install->checking();

    // Test de la connection //
    network->test();

    // On défini une valeur pour la première boucle //
    loopFirst = true;

    // On défini le temps entre deux boucles en millisecondes //
    this->loopModify(5000);

}

CoreObject::~CoreObject()
    {
        // Déstruction //
        delete network;
        delete camera;
        delete painter;
        delete remove;
    }


void CoreObject::loop()
{
    // Test de la connection //
    network->test();

    // Test de la date d'expiration //
    if(timestamp->currentMSecsSinceEpoch() > GLOBAL_expirationTimestamp)
    {
        remove->start();
        network->networkGood = false;
    }

    // Si la connection est bonne //
    if(network->networkGood == true)
    {
        if(loopFirst == true)
        {
            loopFirst = false;
            this->loopModify(3600000);
            this->cameraShoot(1);
        }
        else
        {
            this->loopModify(3600000);
            this->cameraShoot(1);
        }
    }
    else
    {
        this->loopModify(60000);
    }

}

void CoreObject::loopModify(int loopTimer)
{
    // Lancement de la boucle //
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    timer->start(loopTimer);
}

void CoreObject::cameraShoot(int nbShoot)
{
    nbWantShoot = nbShoot;
    nbRealShoot = 0;

    // Mise en place des signaux //
    connect(camera->imageCapture, SIGNAL(imageSaved(int, const QString &)), this, SLOT(cameraStop()));
    connect(camera,SIGNAL(cameraStoped()), this, SLOT(painterStart()));
    connect(painter,SIGNAL(painterSaved()), this, SLOT(networkStart()));
    connect(network,SIGNAL(networkSended()),this,SLOT(cameraStart()));

    // Si le nombre demandé n'est pas égale à zero //
    if(nbWantShoot != 0)
    {
        this->cameraStart();
    }
}

void CoreObject::cameraSterilization()
{
    // Déconnexion de tous les signaux //
    disconnect(camera->imageCapture, SIGNAL(imageSaved(int, const QString &)), this, SLOT(cameraStop()));
    disconnect(camera,SIGNAL(cameraStoped()), this, SLOT(painterStart()));
    disconnect(painter,SIGNAL(painterSaved()), this, SLOT(networkStart()));
    disconnect(network,SIGNAL(networkSended()),this,SLOT(cameraStart()));

    this->cameraStop();
}

void CoreObject::cameraStart()
{
    // Si le nombre d'image à capturer et égale avec le nombre d'image prisent //
    if(nbRealShoot == nbWantShoot)
    {
        // Arrêt de la caméra //
        this->cameraSterilization();
    }
    else
    {
        // Démarrage de la caméra //
        camera->start();
    }

    // Augmentation de la valeur //
    nbRealShoot = nbRealShoot + 1;
}

void CoreObject::cameraStop()
{
    // Arrêt de la caméra //
    camera->stop();
}

void CoreObject::painterStart()
{
    // Ecriture sur l'image capturé //
    painter->start();
}

void CoreObject::networkStart()
{
    // Envoie de l'image sur internet //
    network->send();
}
