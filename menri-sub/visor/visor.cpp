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
    //delete imagenVista;
    delete ui;
}

void visor::cargarImagen(QPixmap img)
{
    //imagenVista = new  QPixmap(img);

    int w = ui->lblVisor->width();
    int h = ui->lblVisor->height();
    //ui->lblVisor->setPixmap(imagenVista->scaled(w,h,Qt::KeepAspectRatio));
    ui->lblVisor->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));

}

void visor::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton ){
        move(ev->globalPos() - posicionVentana);
        ev->accept();
    }
}

void visor::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        posicionVentana = ev->globalPos() - frameGeometry().topLeft();
        ev->accept();
    }

}

