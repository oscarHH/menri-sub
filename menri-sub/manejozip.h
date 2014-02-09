#ifndef MANEJOZIP_H
#include <QString>
#include <quazipfile.h>
#include <quazipfileinfo.h>
#include <quazip.h>
#include <QList>
#include <QThread>
#include "tipoarchivo.h"
#include <QPixmap>

#define MANEJOZIP_H

class ManejoZip: public QThread
{
     Q_OBJECT

public:
    ManejoZip(QObject*);
    QList<TipoArchivo > getListarArchivos();
    QString getComentarios(); 
    int totalArchivos;
    void setArchivoZip(QString nombreZip);
    void setRutaDescompresion(QString rutaDescompresion);
    void setOpcion(int);
    void setNombreArchivo(QString);
    void detenerHilo();

protected:
  virtual  void  run();

private:
    QString archivoZip;
    QString respaldo;
    QuaZip zip;
    QString rutaDescompresion;
    QString comentarios;
    QList<TipoArchivo > datos;
    volatile bool detener;
    QMutex mutex;
    QString nombreArchivo;
    int opcion;

signals:
    void valor(unsigned int);
    void imagen(QPixmap );

};

#endif // MANEJOZIP_H
