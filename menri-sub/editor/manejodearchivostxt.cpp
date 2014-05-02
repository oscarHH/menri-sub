#include "manejodearchivostxt.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>


ManejoDearchivosTxt::ManejoDearchivosTxt(QString ruta)
{
    this->ruta = ruta;
}

//----------------metodos lectura de archivos---------------
void ManejoDearchivosTxt::setRutaArchivo(QString ruta)
{
    this->ruta = ruta;
}

QString ManejoDearchivosTxt::leerArchivo()
{
    //ruta del archivo
    QFile file (this->ruta);
    file.open(QFile::ReadOnly | QFile::Text);
    //lectura del archivo
    QTextStream contenido(&file);
    //contenido del archivo
    return contenido.readAll();
}
//---------------metodos para guardar los archivos ------------------
void ManejoDearchivosTxt::setRutaGuardar(QString ruta)
{
    this->rutaGuardar = ruta;
}

bool ManejoDearchivosTxt::archivoGuardar(QString datos)
{
    QFile file(rutaGuardar);


    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    qDebug()<<rutaGuardar;
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out << datos;

    file.close();
}

