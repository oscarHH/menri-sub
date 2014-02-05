#include "manejozip.h"
#include <QDebug>
#include <quazipfileinfo.h>
#include<QMessageBox>
ManejoZip::ManejoZip(QObject*parent):QThread(parent)
{
    detener = false;
}
bool det  = true;
//asigna el nombre del zip
void ManejoZip::setArchivoZip(QString nombreZip)
{
    this->archivoZip = nombreZip;
    this->detener =false;

}


//obtiene los datos de cada archivo comprimido
QList<TipoArchivo > ManejoZip::getListarArchivos()
{
    if(!archivoZip.isEmpty()){
        respaldo = archivoZip;
    }

    zip.setZipName(archivoZip);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //clase para obtener informacion de los archivos comprimidos
    QuaZipFile inf (&zip);
    //borrar datos de los archivos
    datos.clear();

    //agregamos la informacion de cada archivo comprimido
    for(bool more = zip.goToFirstFile();more;more=zip.goToNextFile()){
        TipoArchivo  tip(inf.getActualFileName(),inf.usize(),inf.csize());
        tip.setTipoArchivo(inf.getActualFileName());
        datos.append(tip);

    }
    //cierra zip
    zip.close();
    //ordenando los datos
    qSort(datos.begin(),datos.end(),qLess<TipoArchivo>());
    qDebug()<<zip.getZipError();
    this->totalArchivos = datos.size();
    return datos;
}



//retorna el comentario del zip
QString ManejoZip::getComentarios()
{
    //abre el zip
    zip.open(QuaZip::mdUnzip);
    //accionamos la codificacion del comentario
    zip.setCommentCodec(QTextCodec::codecForLocale());
    //obtiene el comentario
    QString comentario = zip.getComment();
    zip.close();
    qDebug()<<zip.getZipError();
    if (!comentario.isEmpty() ){
        return comentario;
    }else{
        return "";
    }
}


void ManejoZip::setRutaDescompresion(QString rutaDescompresion)
{
    this->rutaDescompresion = rutaDescompresion;
}

void ManejoZip::setDetener(bool detener)
{
    this->detener = detener;
}

void ManejoZip::detenerHilo()
{
    mutex.lock();
    this->detener = true;
    mutex.unlock();
}



void ManejoZip::run()
{


    unsigned int i =0;
    qDebug()<<totalArchivos;
    QByteArray ba;
    zip.open(QuaZip::mdUnzip);
    for(bool more = zip.goToFirstFile();more  ;more = zip.goToNextFile()){
        mutex.lock();
        if(detener){
           detener = false;
            mutex.unlock();
            break;
        }

        QString filePath = zip.getCurrentFileName();
        QuaZipFile zFile( zip.getZipName(), filePath );
        zFile.open( QIODevice::ReadOnly );
        ba =zFile.read(zFile.size());
        zFile.close();
        //la ruta donde se guardara + el nobre del archivo
        QFile dstFile( rutaDescompresion+filePath );
        dstFile.open( QIODevice::WriteOnly);
        dstFile.write( ba);
        dstFile.close();
        ba.clear();
        ++i;
        mutex.unlock();
        emit valor(i);
    }
    zip.close();

    qDebug()<<detener;
    qDebug()<<"fin";
}



