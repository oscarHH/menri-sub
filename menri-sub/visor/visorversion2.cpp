#include "visorversion2.h"
#include <cmath>
#include <QDebug>
#include <QGraphicsRectItem>



//metodo constructor de la clase 
VisorVersion2::VisorVersion2(QWidget */*parent*/)
{
    scene = new QGraphicsScene;
    this->setScene (scene);
    item = new QGraphicsPixmapItem(QPixmap(":/img/iconos/portada.png"));
    scene->addItem (item);
    //this->setDragMode (QGraphicsView::ScrollHandDrag);
    this->scale (0.3,0.3);
    //this->tamanio = 1.0; 
}


QColor VisorVersion2::getColor() const
{
    return color;
}

void VisorVersion2::setColor(const QColor &value)
{
    color = value;
    this->setBackgroundBrush (color);
    
}
QString VisorVersion2::getRuta() const
{
    return ruta;
}

void VisorVersion2::setRuta(const QString &value)
{
    ruta = value;
    item->setPixmap (QPixmap(ruta)); //agrega la imagen
    this->setDragMode (QGraphicsView::ScrollHandDrag );
    this->setSceneRect (item->boundingRect ());   //ajusta al tamaño de la imagen    
    this->setScene (scene);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
    this->centerOn (0,0);
    
}
int VisorVersion2::getGrados() const
{
    return grados;
}

void VisorVersion2::setGrados(int value)
{
    grados = value;
    this->rotate (grados);
}



qreal VisorVersion2::getTamanio() const
{
    return tamanio;

}

void VisorVersion2::setTamanio(const qreal &value)
{
    tamanio = value;
    this->scale(tamanio,tamanio);
}

