#include "EventosZip.h"



EventosZip::EventosZip()
{

}

void EventosZip::setListar(QString ruta)
{
    //solo visualisa los archivos que estan dentro del zip
    //lista de string almacena los nombre de los archivos en zip
    //asigna el nombre del archivo zip
    //QuaZip zip("F:/com/com.zip");
    QuaZip zip(ruta);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //obtener comentarios
    QByteArray comment = zip.getComment().toLocal8Bit();
    setComentario(comment);
    qDebug()<< comment;
    listaArchivos = zip.getFileNameList();
    zip.close();

}


QStringList EventosZip::getListarzip()
{
    return listaArchivos;
}

void EventosZip::descomprimir(QString archivo,QString rutaDescompresion)
{
    qDebug()<<rutaDescompresion;
    QuaZip zip(archivo);
       //abre el archivo
       zip.open(QuaZip::mdUnzip);
       //obtenemos los comentarios del archivo zip
       for(bool more = zip.goToFirstFile();more ;more = zip.goToNextFile()){
           //nombre del zip
           QString filePath = zip.getCurrentFileName();
           //qDebug()<<"nombre imagenes"<<filePath;
           QuaZipFile zFile( zip.getZipName(), filePath );
           zFile.open( QIODevice::ReadOnly );
           QByteArray ba = zFile.readAll();
           zFile.close();
           //la ruta donde se guardara + el nobre del archivo
           QFile dstFile( rutaDescompresion+filePath );
           dstFile.open( QIODevice::WriteOnly);
           dstFile.write( ba);
           dstFile.close();
       }
       zip.close();
}

void EventosZip::setComentario(QString coment)
{
    comentario = coment;
}

QString EventosZip::getComentario()
{
    return comentario;
}


