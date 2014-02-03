#ifndef MANEJOZIP_H
#include <QString>
#include <quazipfile.h>
#include <quazipfileinfo.h>
#include <quazip.h>
#include <QList>
#include "tipoarchivo.h"
//#include <QtAlgorithms>
#define MANEJOZIP_H

class ManejoZip
{
public:
    ManejoZip();
    void setArchivoZip(QString nombreZip);
    QList<TipoArchivo > getListarArchivos();
    QString getComentarios();
    bool descomprimir();
    bool descomprimirIndividual();


private:
    QString archivoZip;
    QString respaldo;
    QuaZip zip;

    QString comentarios;
    QList<TipoArchivo > datos;

};

#endif // MANEJOZIP_H
