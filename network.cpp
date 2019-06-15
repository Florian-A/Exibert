#include <global.h>
#include <network.h>

NetworkObject::NetworkObject(QObject *parent) : QObject(parent)
{
    // Définition des objets //
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QFile *file;
    QNetworkRequest *request;

    // Déclaration des objets non utilisés //
    Q_UNUSED(reply);
    Q_UNUSED(manager);
    Q_UNUSED(file);
    Q_UNUSED(request);

    // Définition que le reseau n'est pas bon //
    networkGood = false;

    // Limite totale de la requête //
    boundary = "----87142694621188";

    // Saut de ligne //
    cr = "\r\n";
}

void NetworkObject::test()
{
    // Création des objets //
    QUrl url = QUrl(GLOBAL_networkTestUrl);
    QNetworkRequest request(url);
    QNetworkAccessManager * manager = new QNetworkAccessManager;

    // Création d'un signal avec lancement //
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(testReply(QNetworkReply*)));
    manager->get(request);
}

void NetworkObject::testReply(QNetworkReply *reply)
{
    // S'il n'y a pas d'erreur lors de la tentative de connexion //
    if(QNetworkReply::NoError == reply->error())
    {
        networkGood = true;
    }
    else
    {
        networkGood = false;
    }
}

void NetworkObject::send()
{
    // Ouverture de l'image et stockage //
    QFile file(GLOBAL_cameraPath);
    file.open(QIODevice::ReadOnly);
    fileContent = file.readAll();

    // Ouverture de l'adresse //
    QUrl url(GLOBAL_networkSendUrl);
    QNetworkRequest request(url);

    // En tête de la requête //
    request.setRawHeader( "Content-Type", "multipart/form-data; boundary=" + boundary );

    // Requête //
    data.append("--" + boundary + cr);
    data.append("Content-Disposition: form-data; name=\"MAX_FILE_SIZE\"" + cr + cr + "67108864" + cr);
    data.append("--" + boundary + cr);
    data.append("Content-Disposition: form-data; name=\"userfile\"; filename=\"" + file.fileName() + "\";" + cr);
    data.append("Content-Type: image/jpeg" + cr + cr);
    data.append(fileContent);
    data.append(cr);
    data.append("--" + boundary  + "--" + cr);

    // En tête de la requête avec la taille de la requête //
    request.setRawHeader( "Content-Length", QString::number(data.size()).toUtf8());

    // Lancement de la requête //
    reply = manager.post(request,data);

    // Réponse de la requête //
    connect(reply,SIGNAL(finished()),this,SLOT(done()));
}

void NetworkObject::done()
{
    // Lancement du signal //
    emit networkSended();
}
