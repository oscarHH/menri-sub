#include "configuraciones.h"
#include "ui_configuraciones.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
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
//abrir dialogo de fondos
void Configuraciones::on_pushButton_5_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 10), this);
    qDebug()<<font.family();
    qDebug()<<font.pointSize();
    ui->txtFuente->setText(font.family());
    ui->tamanioLetra->setText(QString::number( font.pointSize()));
}

//boton cancelar dialogo
void Configuraciones::on_pushButton_6_clicked()
{
    this->close();
}

//abrir dialogo seleccion de colores
void Configuraciones::on_pushButton_9_clicked()
{
     QPalette paleta;
     QColor color;
     color = QColorDialog::getColor(Qt::white,this);
     paleta.setColor(QPalette::Base,color);
     ui->lineEdit_5->setPalette(paleta);
}

//color en p
void Configuraciones::on_pushButton_clicked()
{

}
