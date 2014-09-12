#ifndef VISORVERSION2_H
#define VISORVERSION2_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QBoxLayout>

class VisorVersion2 : public QGraphicsView
{
    Q_OBJECT
public:
    VisorVersion2(QWidget *parent=0);
    QGraphicsScene  * scene ;
    QGraphicsPixmapItem * item;
//signals:
    
    
public slots:
    void mostrarImagen(QString ruta);
    void rotarImagen(int grados);
    void escalarImagen(qreal tamanio);
    
};

#endif // VISORVERSION2_H
