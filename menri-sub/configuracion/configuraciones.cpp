#include "configuraciones.h"
#include "ui_configuraciones.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>

//atributos de clase pra almacenar los colores
QColor respaldo1;
QColor respaldo2;
QFont  respaldo3;
bool  cambioFormato = false;
bool cambioColorLetra = false;
bool cambioColorFondo = false;

//metodo construcotr
Configuraciones::Configuraciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuraciones)
{

    ui->setupUi(this);
    connect(ui->btnColor,SIGNAL(clicked()),this,SLOT(cambiarColor()));

    QSettings settings("menri-sub", "menri-sub");

    QPalette paleta;
    bool primeravez = qvariant_cast<bool>(settings.value("primer inicio"));
    if(!primeravez){
        paleta.setColor(QPalette::Base,Qt::black);
        ui->lineEdit_5->setPalette(paleta);
        paleta.setColor(QPalette::Base,Qt::white);
        ui->lineEdit_6->setPalette(paleta);
        font.setFamily("Arial");
        font.setPointSize(12);
        ui->txtFuente->setText(font.family());
        ui->tamanioLetra->setText(QString::number(font.pointSize()));

        respaldo1 = Qt::black;
        color = respaldo1;
        respaldo2 = Qt::white;
        colorFondo = respaldo2;
        respaldo3 = font;

        return;
    }

    respaldo1 =  qvariant_cast<QColor>(settings.value("color Texto"));
    color = respaldo1;
    paleta.setColor(QPalette::Base,respaldo1);
    ui->lineEdit_5->setPalette(paleta);

    respaldo2 = qvariant_cast<QColor>(settings.value("color Fondo"));
    colorFondo = respaldo2;
    paleta.setColor(QPalette::Base,respaldo2);
    ui->lineEdit_6->setPalette(paleta);

    respaldo3 = qvariant_cast<QFont>(settings.value("fuente beta"));
    ui->txtFuente->setText(respaldo3.family());
    ui->tamanioLetra->setText(QString::number(respaldo3.pointSize()));
}

//metodo destructor
Configuraciones::~Configuraciones()
{
}

//metodo que emite la informacion del color
void Configuraciones::mandarcolor()
{
    if(cambioColorLetra){
        emit valorColor(color);
    }

    if(cambioColorFondo){
        emit valorColorFondo(colorFondo);
    }
}

//metodo que emite la informacion del tipo de letra
void Configuraciones::mandarFormatoLetra()
{
    if(cambioFormato){
        emit valorFormatoLetra(font);
    }

}

//acciones de cuando se da click en el boton aceptar
void Configuraciones::on_btnAceptar_clicked()
{
    this->mandarcolor();
    this->mandarFormatoLetra();
    this->close();
    guardarConfiguracion();

}

//cierra la ventana de configuracion
void Configuraciones::on_btnCancelar_clicked()
{
    this->close();
}

//fuente de letra del editor
void Configuraciones::on_btnFuente_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, QFont(respaldo3.family(), respaldo3.pointSize()), this);
    if (ok){
        ui->txtFuente->setText(font.family());
        ui->tamanioLetra->setText(QString::number( font.pointSize()));
        respaldo3 = font;
        cambioFormato = true;
    }else{
        font = respaldo3;
        ui->txtFuente->setText(font.family());
        ui->tamanioLetra->setText(QString::number( font.pointSize()));
        cambioFormato = false;
    }

}

//boton para cambiar el   color de letra del editor de texto
void Configuraciones::cambiarColor()
{
    QPalette paleta;
    color = QColorDialog::getColor(Qt::white,this);
    if(color.isValid()){
        paleta.setColor(QPalette::Base,color);
        ui->lineEdit_5->setPalette(paleta);
        respaldo1 = color;
        cambioColorLetra = true;
    }else{
        color = respaldo1;
        //paleta.setColor(QPalette::Base,color);
        //ui->lineEdit_5->setPalette(paleta);
        cambioColorLetra = false;
    }

}

//boton para cambiar el fondo de color del editor de texto
void Configuraciones::on_btnColorFondo_clicked()
{
    QPalette paleta;
    colorFondo = QColorDialog::getColor(Qt::white,this);
    if(colorFondo.isValid()){
        paleta.setColor(QPalette::Base,colorFondo);
        ui->lineEdit_6->setPalette(paleta);
        respaldo2 = colorFondo;
        cambioColorFondo = true;
    }else{
        colorFondo = respaldo2;
       // paleta.setColor(QPalette::Base,colorFondo);
        //ui->lineEdit_6->setPalette(paleta);
        cambioColorFondo = false;
    }

}

//metodo que guarda la configuracion
void Configuraciones::guardarConfiguracion()
{
    QSettings settings("menri-sub", "menri-sub");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("color Texto",color);
    settings.setValue("color Fondo",colorFondo);
    settings.setValue("fuente beta",font);
    settings.setValue("primer inicio",true);
}
