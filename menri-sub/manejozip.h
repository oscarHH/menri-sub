#ifndef MANEJOZIP_H
#include <QString>
#include <quazipfile.h>
#include <quazip.h>


#define MANEJOZIP_H



class ManejoZip
{
public:
    ManejoZip();
    void setArchivoZip(QString nombreZip);
    QStringList getListarArchivos();
    QString getComentarios();

private:
    QString archivoZip;
    QString respaldo;
    QuaZip zip;
    QStringList listaArchivos;
    QString comentarios;

};

#endif // MANEJOZIP_H
