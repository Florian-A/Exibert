#include <core.h>

// Fonction coeur de démarrage //
int main(int argc, char *argv[])
{
    // Fonction coeur de démarrage pour Qt //
    QApplication app(argc, argv);
    CoreObject * core = new CoreObject();

    // Déclaration des objets non utilisés //
    Q_UNUSED(core);

    return app.exec();
}
