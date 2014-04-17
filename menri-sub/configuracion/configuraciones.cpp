#include "configuraciones.h"
#include "ui_configuraciones.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>



Configuraciones::Configuraciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuraciones)
{
    ui->setupUi(this);
    connect(ui->btnColor,SIGNAL(clicked()),this,SLOT(cambiarColor()));
}

Configuraciones::~Configuraciones()
{
}

void Configuraciones::mandarcolor()
{
    emit valorColor(color,colorFondo);
}

void Configuraciones::mandarFormatoLetra()
{
    emit valorFormatoLetra(font);
}


void Configuraciones::cambiarColor()
{
    QPalette paleta;
    color = QColorDialog::getColor(Qt::white,this);
    paleta.setColor(QPalette::Base,color);
    ui->lineEdit_5->setPalette(paleta);
}


void Configuraciones::on_btnAceptar_clicked()
{
    this->mandarcolor();
    this->mandarFormatoLetra();

}

void Configuraciones::on_btnCancelar_clicked()
{
    this->close();
}

void Configuraciones::on_btnFuente_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, QFont("Times", 10), this);
    ui->txtFuente->setText(font.family());
    ui->tamanioLetra->setText(QString::number( font.pointSize()));
}

void Configuraciones::on_btnColorFondo_clicked()
{
    QPalette paleta;
    colorFondo = QColorDialog::getColor(Qt::white,this);
    paleta.setColor(QPalette::Base,colorFondo);
    ui->lineEdit_6->setPalette(paleta);
}

void Configuraciones::guardarConfiguracion()
{
    QSettings configuracion("Menri-sub","Herramienta");


}
