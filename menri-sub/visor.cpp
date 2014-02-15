#include "visor.h"
#include "ui_visor.h"

visor::visor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::visor)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::FramelessWindowHint);
    setStyleSheet("background-color: rgba(255, 255, 255, 60);");

}

visor::~visor()
{
    delete ui;
    delete imagenVista;
}

void visor::cargarImagen(QPixmap img)
{
    this->imagenVista = new  QPixmap(img);
    int w = ui->lblVisor->width();
    int h = ui->lblVisor->height();
    ui->lblVisor->setPixmap(imagenVista->scaled(w,h,Qt::KeepAspectRatio));

}

