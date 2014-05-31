#ifndef CONFIGURACIONES_H
#define CONFIGURACIONES_H

#include <QDialog>
#include "agregarnuevapalabra.h"
#include "../editor/manejodearchivostxt.h"
namespace Ui {
class Configuraciones;
}

class Configuraciones : public QDialog
{
    Q_OBJECT


public:
    explicit Configuraciones(QWidget *parent = 0);
    ~Configuraciones();


    QColor color;
    QColor colorFondo;
    QFont font;

    void mandarcolor();
    void mandarFormatoLetra();
    void cargarPalabras();

private slots:

    void cambiarColor();
    void on_btnAceptar_clicked();


    void on_btnCancelar_clicked();

    void on_btnFuente_clicked();

    void on_btnColorFondo_clicked();

    void guardarConfiguracion();

    void on_pushButton_clicked();

private:
    Ui::Configuraciones *ui;

signals:
    void valorColor (const QColor);
    void valorFormatoLetra(const QFont);
    void valorColorFondo (const QColor);
};

#endif // CONFIGURACIONES_H
