#include <global.h>
#include <painter.h>

PainterObject::PainterObject(QObject *parent) : QObject(parent)
{
    // Définition des objets //
    QImage *image;
    QPainter *painter;
    QFont *font;

    // Déclaration des objets non utilisés //
    Q_UNUSED(image);
    Q_UNUSED(painter);
    Q_UNUSED(font);
}

void PainterObject::start()
{
    // Ouverture de l'image //
    QImage image(GLOBAL_cameraPath);

    // Paramétrage de la taille de l'image //
    pixmap = new QPixmap(image.width(),image.height());

    // Conversion de l'image //
    pixmap->convertFromImage(image);

    // Paramétrage avec l'espace de dessin //
    QPainter painter(pixmap);

    // Paramétrage de la police et taille d'écriture //
    QFont font("Courier New", 14);

    // Mise à jour de la date et gps dans une variable //
    QString date = QDateTime::currentDateTime().toString("hh:mm:ss dddd d MMMM yyyy");

    QString gpscoords = QString::number(gps.latitude()) + QString::number(gps.longitude()) + QString::number(gps.altitude());

    QString text = gpscoords + date;

    // Exécution des fonctions de dessins //
    painter.setFont(font);
    painter.setPen(QPen(QColor(0,255,0)));
    painter.setClipping(true);
    painter.drawText(QRect(20, 20, 600, 200), Qt::TextWordWrap, text);

    // Enregistrement de l'image avec une compression //
    pixmap->save(GLOBAL_cameraPath,"JPG", 95);

    // Lancement du signal //
    emit painterSaved();
}
