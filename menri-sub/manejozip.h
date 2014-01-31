#ifndef MANEJOZIP_H
#include <QString>
#include <quazipfile.h>
#include <quazip.h>
#include <QList>
#include "tipoarchivo.h"

#define MANEJOZIP_H

class ManejoZip
{
public:
    ManejoZip();
    void setArchivoZip(QString nombreZip);
    QStringList getListarArchivos();
    QString getComentarios();
    QString getTipoArchivo();
    QString getFechaModificacion();
    QString getCrc();
    double getTamanioArchivo();
    double getTamanioComprimido();


private:
    QString archivoZip;
    QString respaldo;
    QuaZip zip;
    QStringList listaArchivos;
    QString comentarios;
    QList<TipoArchivo *> datos;

};

#endif // MANEJOZIP_H
