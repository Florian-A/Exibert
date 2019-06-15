#ifndef PAINTEROBJECT_H
#define PAINTEROBJECT_H

#include <QImage>
#include <QPainter>
#include <QFont>
#include <QDateTime>
#include <QGeoCoordinate>

class PainterObject : public QObject
{
    Q_OBJECT
    public:
        explicit PainterObject(QObject *parent = 0);

    public slots:

        void start();

    private:

        QPixmap* pixmap;
        QImage image;
        QPainter painter;
        QFont font;
        QGeoCoordinate gps;

    signals:

        void painterSaved();
};

#endif // PAINTEROBJECT_H
