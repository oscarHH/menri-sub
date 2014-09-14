#ifndef VISORVERSION2_H
#define VISORVERSION2_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QColor>

class VisorVersion2 : public QGraphicsView
{
    Q_OBJECT
public:
    VisorVersion2(QWidget *parent=0);
    QGraphicsScene  * scene ;
    QGraphicsPixmapItem * item;

    //set y get 
    QColor getColor() const;

    
    QString getRuta() const;
    void setRuta(const QString &value);
    
    int getGrados() const;
    void setGrados(int value);
    
    qreal getTamanio() const;
    void setTamanio(const qreal &value);
    
private:
    QColor color;
    QString ruta;
    int grados;
    qreal tamanio;    
//signals:    
public slots:
       void setColor(const QColor &value);
};

#endif // VISORVERSION2_H
