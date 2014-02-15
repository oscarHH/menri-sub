#include "configuraciones.h"
#include "ui_configuraciones.h"

Configuraciones::Configuraciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuraciones)
{
    ui->setupUi(this);
}

Configuraciones::~Configuraciones()
{
    delete ui;
}
