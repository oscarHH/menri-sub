#include "manejozip.h"
#include <QDebug>
#include <quazipfileinfo.h>
ManejoZip::ManejoZip()
{    
}

//asigna el nombre del zip
void ManejoZip::setArchivoZip(QString nombreZip)
{
    this->archivoZip = nombreZip;
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

    zip.close();
    qSort(datos.begin(),datos.end(),qLess<TipoArchivo>());
    foreach (TipoArchivo a, datos) {
        qDebug()<<a.getNombreDelArchivo();
    }
    return datos;
}

QStringList ManejoZip::getListarArchivos2(){
    if(!archivoZip.isEmpty()){
        respaldo = archivoZip;
    }

    QString informacion;

    zip.setZipName(archivoZip);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //clase para obtener informacion de los archivos comprimidos
    QuaZipFile inf (&zip);
    for(bool more = zip.goToFirstFile();more;more=zip.goToNextFile()){
        inf.open(QIODevice::ReadOnly);
        informacion = inf.getActualFileName() + "-" + QString::number(inf.size()) + "-" +QString::number(inf.csize());
        inf.close();
        datos2.append(informacion);
    }

    zip.close();
    return datos2;
}

bool ManejoZip::dtcomp(TipoArchivo &a, TipoArchivo &b)
{
    return &a.getNombreDelArchivo() < &b.getNombreDelArchivo();
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
    if (!comentario.isEmpty() ){
        return comentario;
    }else{
        return "";
    }
}

//retorna true si se descomprimio
bool ManejoZip::descomprimir()
{
    return true;
}


