#ifndef CONFIGURACIONES_H
#define CONFIGURACIONES_H

#include <QDialog>

namespace Ui {
class Configuraciones;
}

class Configuraciones : public QDialog
{
    Q_OBJECT

public:
    explicit Configuraciones(QWidget *parent = 0);
    ~Configuraciones();

private:
    Ui::Configuraciones *ui;
};

#endif // CONFIGURACIONES_H
