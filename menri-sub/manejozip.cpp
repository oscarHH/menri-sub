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
    QuaZipFile inf(&zip);
    datos.clear();

    //datos = new QList<TipoArchivo>;
    for(bool more = zip.goToFirstFile();more;more=zip.goToNextFile()){
        TipoArchivo * tip = new TipoArchivo;
        tip->setNombreDelArchivo(inf.getActualFileName());
        datos.append(tip);
    }

    for(int i=0; i< datos.size()  ;i++){
        qDebug()<< datos.at(i)->getNombreDelArchivo();
    }




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
    QString comentario = zip.getComment();
    zip.close();
    if (!comentario.isEmpty() ){
        return comentario;
    }else{
        return "";
    }
}
