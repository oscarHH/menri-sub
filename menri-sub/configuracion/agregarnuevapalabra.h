#ifndef AGREGARNUEVAPALABRA_H
#define AGREGARNUEVAPALABRA_H

#include <QDialog>
#include "datosconfiguracion.h"

namespace Ui {
class AgregarNuevaPalabra;
}

class AgregarNuevaPalabra : public QDialog
{
    Q_OBJECT
    QColor color;

    datosConfiguracion dconfig;
public:
    explicit AgregarNuevaPalabra(QWidget *parent = 0);
    ~AgregarNuevaPalabra();
    datosConfiguracion getConfig()const {return dconfig;}

private slots:
    void on_btnCancelar_clicked();
    void on_btnAceptar_clicked();

    void on_txtPalabra_textEdited(const QString &arg1);
    void on_btnColor_clicked();



private:
    Ui::AgregarNuevaPalabra *ui;

};

#endif // AGREGARNUEVAPALABRA_H
