#include "tipoarchivo.h"

TipoArchivo::TipoArchivo()
{
}

void TipoArchivo::setNombreDelArchivo(QString nombreDelArchivo)
{
    this->nombreDelArchivo = nombreDelArchivo;
}

QString TipoArchivo::getNombreDelArchivo()
{
    return nombreDelArchivo;
}

