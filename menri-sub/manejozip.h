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
    QString getTipoArchivo();
    QString getFechaModificacion();
    QString getCrc();
    double getTamanioArchivo();
    double getTamanioComprimido();
    bool descomprimir();
    bool descomprimirIndividual();
    QStringList getListarArchivos2();
    bool dtcomp(TipoArchivo &a ,  TipoArchivo &b);

private:
    QString archivoZip;
    QString respaldo;
    QuaZip zip;
    QStringList listaArchivos;
    QString comentarios;
    QList<TipoArchivo > datos;
    QStringList datos2;
};

#endif // MANEJOZIP_H
