#include "manejozip.h"
#include <QDebug>
#include <quazipfileinfo.h>
#include<QMessageBox>



ManejoZip::ManejoZip(QObject*parent):QThread(parent)
{
    detener = false;

}

ManejoZip::~ManejoZip()
{

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
    int i =1;
    zip.setZipName(archivoZip);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //clase para obtener informacion de los archivos comprimidos
    QuaZipFile inf (&zip);
    //borrar datos de los archivos
    datos.clear();
    QStringList dat = zip.getFileNameList();
    foreach (QString n, dat) {
        qDebug()<<n;
        i++;
    }


    //agregamos la informacion de cada archivo comprimido
    for(bool more = zip.goToFirstFile();more;more=zip.goToNextFile()){
        TipoArchivo  tip(inf.getActualFileName(),inf.usize(),inf.csize());
        tip.setTipoArchivo(inf.getActualFileName());
        datos.append(tip);

    }
    qDebug()<<i;
    //cierra zip
    zip.close();



    //ordenando los datos
    qSort(datos.begin(),datos.end(),qLess<TipoArchivo>());

    /*foreach (TipoArchivo tp, datos) {
        qDebug()<< "ren"<<tp.getNombreDelArchivo();
    }*/
    this->totalArchivos = datos.size();
    return datos;
}



//retorna el comentario del zip
QString ManejoZip::getComentarios()
{
    //abre el zip
    zip.open(QuaZip::mdUnzip);
    //accionamos la codificacion del comentario
    //zip.setCommentCodec(QTextCodec::codecForName("UTF-8"));
    //obtiene el comentario
    QString comentario =  zip.getComment() ;
    zip.close();


    if (!comentario.isEmpty() ){
        return comentario.toLower();
    }
    return "";
}


void ManejoZip::setRutaDescompresion(QString rutaDescompresion)
{
    this->rutaDescompresion = rutaDescompresion;
}

void ManejoZip::setOpcion(int opcion){
    this->opcion = opcion;
}


void ManejoZip::setNombreArchivo(QString nombreArchivo){
    this->nombreArchivo = nombreArchivo;
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
    QByteArray ba;
    zip.open(QuaZip::mdUnzip);
    /*
    *opcion
    * 1.- descomprimir todo
    * 2.- descompresion individual
    * 3.- visualizar archivo
    */

    switch (opcion){
    case 1:
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
            dstFile.open( QIODevice::ReadWrite);
            dstFile.write( ba);
            dstFile.close();
            ba.clear();
            ++i;
            mutex.unlock();
            emit valor(i);
        }

        break;

    case 2:
    {
        emit valor(1);
        mutex.lock();
        QuaZipFile zFile(zip.getZipName(),nombreArchivo);
        zFile.open(QIODevice::ReadOnly);
        ba = zFile.read(zFile.size());
        zFile.close();
        //la ruta donde se guardara + el nobre del archivo
        QFile dstFile( rutaDescompresion+nombreArchivo );
        dstFile.open( QIODevice::WriteOnly);
        dstFile.write( ba);
        dstFile.close();
        ba.clear();
        mutex.unlock();
        emit valor(3);
    }
        break;

    case 3:
    {
        QPixmap p;
        emit valor(1);
        mutex.lock();


        QuaZipFile zFile(zip.getZipName(),nombreArchivo);
        zFile.open(QIODevice::ReadOnly);
        ba =zFile.read(zFile.size());
        if(p.loadFromData(ba,"") ){
            emit imagen( p);
        }

        zFile.close();
        ba.clear();
        mutex.unlock();
        emit valor(3);
    }
        break;

    default:
        break;

    }
    zip.close();

}
