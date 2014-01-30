#include "manejozip.h"
#include <QDebug>
ManejoZip::ManejoZip()
{    
}

void ManejoZip::setArchivoZip(QString nombreZip)
{
    this->archivoZip = nombreZip;
}


QStringList ManejoZip::getListarArchivos()
{
    if(!archivoZip.isEmpty())
        respaldo = archivoZip;
    zip.setZipName(archivoZip);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    listaArchivos = zip.getFileNameList();
    zip.close();
    return listaArchivos;
}

QString ManejoZip::getComentarios()
{
    //abre el zip
    zip.open(QuaZip::mdUnzip);
    //accionamos la codificacion del comentario
    zip.setCommentCodec(QTextCodec::codecForLocale());
    //obtiene el comentario
    QString comentario = zip.getComment().toUtf8();
    zip.close();
    if (!comentario.isEmpty() ){
        return comentario;
    }else{
        return "";
    }



}
