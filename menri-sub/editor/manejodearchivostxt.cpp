#include "manejodearchivostxt.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

QStringList rutaArchivoProyectos;

ManejoDearchivosTxt::ManejoDearchivosTxt(QString ruta)
{
    this->ruta = ruta;
}

//**********************************metodos lectura de archivos**********************************
//asigna la ruta del archivo
void ManejoDearchivosTxt::setRutaArchivo(QString ruta)
{
    this->ruta = ruta;
}

//metodo que regresa el contenido del txt
QString ManejoDearchivosTxt::leerArchivo()
{
    //ruta del archivo
    QFile file (this->ruta);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
           return "";
    }
    //lectura del archivo
    QTextStream contenido(&file);
    //contenido del archivo
    QString cont =contenido.readAll();

    return cont;

}

//retorna una lista de rutas de las imagenes
QStringList ManejoDearchivosTxt::leerRutas(QString rut)
{
    QStringList rutaImagenes;
    //ruta del archivo
    QFile file (rut);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {

    }
    QTextStream stream(&file);
    QString line;

    do {
        line =stream.readLine();

        if(line.isNull())
            break;

        rutaImagenes.append(line);
    } while (!line.isNull());

    return rutaImagenes;
}


//**********************************metodos para guardar los archivos**********************************
void ManejoDearchivosTxt::setRutaGuardar(QString ruta)
{
    this->rutaGuardar = ruta;
}

QString ManejoDearchivosTxt::getRutaArchivos()
{
    return rutaGuardar;
}

bool ManejoDearchivosTxt::archivoGuardar(QString datos)
{
    QFile file(rutaGuardar);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    //file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out << datos;

    return true;
}



