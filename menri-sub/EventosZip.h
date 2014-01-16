#ifndef EVENTOSZIP_H
#define EVENTOSZIP_H

#include <JlCompress.h>
#include <quazipfile.h>
#include <quazip.h>
#include <zip.h>
#include <QStringList>
#include <QDebug>


class EventosZip
{
public:
    EventosZip();
    ~EventosZip();
    void setListar(QString ruta);
    QStringList  getListarzip();
    void descomprimir(QString archivo,QString rutaDescompresion);
    void setComentario(QString coment);
    QString getComentario();

private:
    QString comentario;
    QStringList listaArchivos;
};

#endif // EVENTOSZIP_H
