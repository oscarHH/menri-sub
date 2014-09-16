#include "configuraciones.h"
#include "ui_configuraciones.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>
#include <QDir>

//atributos de clase pra almacenar los colores
QColor respaldo1;
QColor respaldo2;
QColor respaldo4;
QColor respaldo5;

QFont  respaldo3;
bool  cambioFormato = false;
bool cambioColorLetra = false;
bool cambioColorFondo = false;
bool cambioColorFondoVisor = false;
bool cambioColorLineaActual = false;

ManejoDearchivosTxt *archtxt = new ManejoDearchivosTxt();

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
        paleta.setColor(QPalette::Base,Qt::yellow);
        ui->txtColorLineaActual->setPalette(paleta);
        respaldo1 = Qt::black;
        color = respaldo1;
        respaldo2 = Qt::white;
        colorFondo = respaldo2;
        respaldo3 = font;
        respaldo4 = Qt::white;
        respaldo5 = Qt::yellow;
        
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
    
    respaldo4 = qvariant_cast<QColor>(settings.value("color Fondo Visor"));
    fondoVisor = respaldo4;
    paleta.setColor (QPalette::Base,respaldo4);
    ui->txtFondoColor->setPalette (paleta);
    
    respaldo5 = qvariant_cast<QColor>(settings.value("color Linea Actual"));
    colorLineaActual = respaldo5;
    paleta.setColor (QPalette::Base,respaldo5);
    ui->txtColorLineaActual->setPalette (paleta);
    
    // nuevaPalabra = new AgregarNuevaPalabra(this);
    //qDebug()<<QDir::currentPath();
    
}

//metodo destructor
Configuraciones::~Configuraciones()
{
    delete ui;
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
    
    if(cambioColorFondoVisor){
        emit valorColorFondoVisor(fondoVisor);
    }
    
    if(cambioColorLineaActual){
        emit valorColorLineaActual (colorLineaActual);
    }
    
}

//metodo que emite la informacion del tipo de letra
void Configuraciones::mandarFormatoLetra()
{
    if(cambioFormato){
        emit valorFormatoLetra(font);
    }
    
}

//lee archivo de configuracion
void Configuraciones::cargarPalabras()
{
    
    archtxt->setRutaArchivo(QDir::homePath()+"/.menri-sub/config/recortes.mconfig");
    qDebug()<<archtxt->leerArchivo();
    
}

//acciones de cuando se da click en el boton aceptar
void Configuraciones::on_btnAceptar_clicked()
{
    this->mandarcolor();
    this->mandarFormatoLetra();
    this->close();
    guardarConfiguracion();
    accept();
}

//cierra la ventana de configuracion
void Configuraciones::on_btnCancelar_clicked()
{
    this->close();
}

//fuente de letra del editor
void Configuraciones::on_btnFuente_clicked()
{
    cambioFormato = false;
    bool ok;
    //font = QFontDialog::getFont(&ok, QFont(respaldo3.family(), respaldo3.pointSize()), this);
    font = QFontDialog::getFont(&ok,respaldo3, this);
    if (ok){
        ui->txtFuente->setText(font.family());
        ui->tamanioLetra->setText(QString::number( font.pointSize()));
        respaldo3 = font;
        cambioFormato = true;
    }else{
        font = respaldo3;
        return;
    }
    
}

//boton para cambiar el   color de letra del editor de texto
void Configuraciones::cambiarColor()
{
    cambioColorLetra = false;
    QPalette paleta;
    color = QColorDialog::getColor(Qt::white,this,"Color de letra",QColorDialog::DontUseNativeDialog);
    
    if(color.isValid()){
        paleta.setColor(QPalette::Base,color);
        ui->lineEdit_5->setPalette(paleta);
        respaldo1 = color;
        cambioColorLetra = true;
    }else{
        color = respaldo1;
        return;
    }
    
}

//boton para cambiar el fondo de color del editor de texto
void Configuraciones::on_btnColorFondo_clicked()
{
    
    cambioColorFondo = false;
    QPalette paleta;
    colorFondo = QColorDialog::getColor(Qt::white,this);
    if(colorFondo.isValid()){
        paleta.setColor(QPalette::Base,colorFondo);
        ui->lineEdit_6->setPalette(paleta);
        respaldo2 = colorFondo;
        cambioColorFondo = true;
    }else{
        colorFondo = respaldo2;
        return;
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
    settings.setValue("color Fondo Visor",fondoVisor);
    settings.setValue("fuente beta",font);
    settings.setValue("primer inicio",true);
    settings.setValue("color Linea Actual",colorLineaActual);
    
}

void Configuraciones::on_pushButton_clicked()
{
    AgregarNuevaPalabra nuevaPalabra(this);
    nuevaPalabra.exec();
    datosConfiguracion config =  nuevaPalabra.getConfig();
    qDebug()<< config.getCOlor();
    qDebug()<< config.getPalabra();
}


//obtener el color para asignar de fondo al visor
void Configuraciones::on_btnFondoVisor_clicked()
{
    
    cambioColorFondoVisor = false;
    QPalette paleta;
    fondoVisor = QColorDialog::getColor(Qt::white,this,"Cambiar color de fondo del visor");
    if(fondoVisor.isValid()){
        paleta.setColor(QPalette::Base,fondoVisor);
        ui->txtFondoColor->setPalette(paleta);
        respaldo4 = fondoVisor;
        cambioColorFondoVisor = true;
    }else{
        fondoVisor = respaldo4;
        return;
    }
}

void Configuraciones::on_btnColorLineaActual_clicked()
{
    cambioColorLineaActual= false;
    QPalette paleta;
    colorLineaActual = QColorDialog::getColor(Qt::yellow,this,"Cambiar color de Linea actual");
    if(colorLineaActual.isValid()){
        paleta.setColor(QPalette::Base,colorLineaActual);
        ui->txtColorLineaActual->setPalette(paleta);
        respaldo5 = colorLineaActual;
        cambioColorLineaActual = true;
    }else{
        colorLineaActual = respaldo5;
        return;
    }
}
