#ifndef TIPOARCHIVO_H
#include <QString>
#define TIPOARCHIVO_H

class TipoArchivo
{
public:
    TipoArchivo();
    //nombre del archivo comprimido
    void setNombreDelArchivo(QString);
    QString getNombreDelArchivo();
    //tipo de archivo comprimido
    void setTipoArchivo(QString);
    QString getTipoArchivo();
    //fecha de modificacion del archivo comprimido
    void setFechaModificacion(QString);
    QString getFechaModificacion();
    //crc del archivo comprimido
    void setCrc(QString);
    QString getCrc();
    //tamaño del archivo original
    void setTamanioARchivo(double);
    double getTamanioArchivo();
    //tamaño del archivo comprimido
    void setTamanioComprimido(double);
    double getTamanioComprimido();

private:
    QString nombreDelArchivo;
    QString comentarios;
    QString tiposArchivo;
    QString fechaModificacion;
    QString crc;
    double tamanioArchivo;
    double tamanioComprimido;
};

#endif // TIPOARCHIVO_H
