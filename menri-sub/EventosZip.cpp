#include "EventosZip.h"


EventosZip::EventosZip()
{

}

QStringList EventosZip::listarzip()
{
    //QStringList fonts;
    //fonts <<"ren"<<"sd";

    //solo visualisa los archivos que estan dentro del zip
    //lista de string almacena los nombre de los archivos en zip
    QStringList listaArchivos;
    //asigna el nombre del archivo zip
    QuaZip zip("F:/com/com.zip");
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //visualiza el nombre del archivo zip
    //qDebug()<<zip.getZipName();
    //obtiene y guarda los nombres de los archivos
    listaArchivos = zip.getFileNameList();
    //imprime los nombres de los archivos
    //for(int i =0;  i< re.size();i++){
    //    qDebug() << re.at(i);
    //    qDebug()<<""<<i;
    //}
    //cierra el archivo zip
    zip.close();

    return listaArchivos;
}
