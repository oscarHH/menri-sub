#include "EventosZip.h"


EventosZip::EventosZip()
{

}

QStringList EventosZip::listarzip(QString ruta)
{
    //QStringList fonts;
    //fonts <<"ren"<<"sd";

    //solo visualisa los archivos que estan dentro del zip
    //lista de string almacena los nombre de los archivos en zip
    QStringList listaArchivos;
    //asigna el nombre del archivo zip
    //QuaZip zip("F:/com/com.zip");
    QuaZip zip(ruta);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    listaArchivos = zip.getFileNameList();

    zip.close();

    return listaArchivos;
}

void EventosZip::descomprimir(QString archivo,QString rutaDescompresion)
{
    qDebug()<<rutaDescompresion;
    QuaZip zip(archivo);
       //abre el archivo
       zip.open(QuaZip::mdUnzip);
       //obtenemos los comentarios del archivo zip
       QByteArray comment = zip.getComment().toLocal8Bit();

       qDebug()<<comment;
       for(bool more = zip.goToFirstFile();more ;more = zip.goToNextFile()){
           //nombre del zip
           QString filePath = zip.getCurrentFileName();
           qDebug()<<"nombre imagenes"<<filePath;
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
