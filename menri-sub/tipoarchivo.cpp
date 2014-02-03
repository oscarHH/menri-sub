#include "tipoarchivo.h"

TipoArchivo::TipoArchivo(QString tipo,double tamanio,double comprimido)
{
    this->nombreDelArchivo = tipo;
    this->tamanioArchivo = tamanio;
    this->tamanioComprimido = comprimido;
}

TipoArchivo::TipoArchivo(const TipoArchivo &other)
{
    *this = other;
}

void TipoArchivo::setNombreDelArchivo(QString nombreDelArchivo)
{
    this->nombreDelArchivo = nombreDelArchivo;
}

QString TipoArchivo::getNombreDelArchivo() const
{
    return nombreDelArchivo;
}

void TipoArchivo::setTipoArchivo(QString tipoArchivo )
{
    this->tipoArchivo =tipoArchivo ;
}
QString TipoArchivo::getTipoArchivo()const
{
    if(tipoArchivo.endsWith("/") || tipoArchivo.endsWith("\\") ){
        return"directorio";
    }else if(tipoArchivo.endsWith(".jpg") ||
             tipoArchivo.endsWith(".png") ||
             tipoArchivo.endsWith(".psd") ||
             tipoArchivo.endsWith(".svg") ||
             tipoArchivo.endsWith(".bmp") ||
             tipoArchivo.endsWith(".jpeg")||
             tipoArchivo.endsWith(".gif")){

        return  "Imagen" ;
    }else if(tipoArchivo.endsWith(".txt")){
        return  "Texto";
    }else if(tipoArchivo.endsWith(".avi") ||
             tipoArchivo.endsWith(".mp4") ||
             tipoArchivo.endsWith(".mpg") ){

        return "video";
    }else if(tipoArchivo.endsWith(".mp3")){

        return  "Audio";
    }
    return  "";
}

void TipoArchivo::setTamanioARchivo(double tamanioArchivo)
{
    this->tamanioArchivo = tamanioArchivo;
}

double TipoArchivo::getTamanioArchivo() const
{
    return tamanioArchivo;
}

void TipoArchivo::setTamanioComprimido(double tamanioComprimido )
{
    this->tamanioComprimido  = tamanioComprimido ;
}

double TipoArchivo::getTamanioComprimido() const
{
    return tamanioComprimido;
}



