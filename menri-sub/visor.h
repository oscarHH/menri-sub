#ifndef VISOR_H
#define VISOR_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class visor;
}

class visor : public QDialog
{
    Q_OBJECT

public:
    explicit visor( QWidget *parent = 0);
    ~visor();
    void cargarImagen(QPixmap img);
    //QPixmap *imagenVista;
private:
    Ui::visor *ui;
    QPoint posicionVentana;

protected:
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);


};

#endif // VISOR_H
