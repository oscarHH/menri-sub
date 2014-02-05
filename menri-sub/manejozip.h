#ifndef MANEJOZIP_H
#include <QString>
#include <quazipfile.h>
#include <quazipfileinfo.h>
#include <quazip.h>
#include <QList>
#include <QThread>
#include "tipoarchivo.h"

#define MANEJOZIP_H

class ManejoZip: public QThread
{
     Q_OBJECT

public:
    ManejoZip(QObject*);
    void setArchivoZip(QString nombreZip);
    QList<TipoArchivo > getListarArchivos();
    QString getComentarios();
    bool descomprimir(QString archivo,QString rutaDescompresion);
    bool descomprimirIndividual();
    void setRutaDescompresion(QString rutaDescompresion);
    int totalArchivos;
    void setDetener(bool);
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
signals:
    void valor(unsigned int);

};

#endif // MANEJOZIP_H
