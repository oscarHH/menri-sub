#ifndef VISOR_H
#define VISOR_H

#include <QDialog>

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
    QPixmap *imagenVista;
private:
    Ui::visor *ui;
};

#endif // VISOR_H
