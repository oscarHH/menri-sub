#include "manejodearchivostxt.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

QStringList rutaArchivoProyectos;
ManejoDearchivosTxt::ManejoDearchivosTxt()
{
}

ManejoDearchivosTxt::~ManejoDearchivosTxt()
{
    delete this;
}

//asigna la ruta del archivo
void ManejoDearchivosTxt::setRutaArchivo(QString ruta)
{
    this->ruta = ruta;
}

//**********************************metodos lectura de archivos**********************************


//metodo que regresa el contenido del txt
QString ManejoDearchivosTxt::leerArchivo()
{
    //ruta del archivo
    QFile file (this->ruta);
    QTextStream contenido(&file);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
           return "";
    }

     contenido.setCodec("UTF-8");
    //lectura del archivo

    //contenido del archivo
    QString cont = contenido.readAll() ;

    return cont;
}

//retorna una lista de rutas de las rutas
QStringList ManejoDearchivosTxt::leerRutas(QString rut)
{
    QStringList rutaImagenes;
    //ruta del archivo
    QFile file (rut);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    QString line = "";

    //line = stream.readAll();

    do {
        line =stream.readLine();

        /*if(line.isNull())
            break;*/

        rutaImagenes.append(line);
    } while (!line.isNull());

    return rutaImagenes;
}


//**********************************metodos para guardar los archivos**********************************

QString ManejoDearchivosTxt::getRutaArchivos()
{
    return ruta;
}

bool ManejoDearchivosTxt::archivoGuardar(QString datos)
{
    QFile file(ruta);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    //file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);

    out.setCodec("UTF-8");
    out << datos;

    return true;
}



