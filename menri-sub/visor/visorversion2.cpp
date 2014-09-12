#include "visorversion2.h"
#include <cmath>
#include <QGraphicsRectItem>

VisorVersion2::VisorVersion2(QWidget */*parent*/)
{
    scene = new QGraphicsScene;
    this->setScene (scene);
    item = new QGraphicsPixmapItem(QPixmap(":/img/iconos/portada.png"));
    scene->addItem (item);
    //this->setDragMode (QGraphicsView::ScrollHandDrag);
    this->scale (0.3,0.3);
}

void VisorVersion2::mostrarImagen(QString ruta)
{
      item->setPixmap (QPixmap(ruta)); //agrega la imagen
      this->setDragMode (QGraphicsView::ScrollHandDrag);
      this->setSceneRect (item->boundingRect ());   //ajusta al tamaño de la imagen    
      this->setScene (scene);
      
}

void VisorVersion2::rotarImagen(int grados)
{
    this->rotate (grados);
}

void VisorVersion2::escalarImagen(qreal tamanio)
{
     this->scale(tamanio, tamanio);
}
