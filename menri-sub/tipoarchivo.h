#ifndef TIPOARCHIVO_H
#include <QString>
#define TIPOARCHIVO_H

class TipoArchivo
{
public:

    TipoArchivo(QString tipo,double tamanio,double comprimido);
    TipoArchivo(const TipoArchivo &other);
    ~TipoArchivo();
    //nombre del archivo comprimido
    void setNombreDelArchivo(QString) ;
    QString getNombreDelArchivo() const;
    //tipo de archivo comprimido
    void setTipoArchivo(QString);
    QString getTipoArchivo() const;
    //tamaño del archivo original
    void setTamanioARchivo(double);
    double getTamanioArchivo() const;
    //tamaño del archivo comprimido
    void setTamanioComprimido(double);

    double getTamanioComprimido() const;
    TipoArchivo & operator = (const TipoArchivo &other){
        nombreDelArchivo = other.nombreDelArchivo;
        tipoArchivo = other.tipoArchivo;
        tamanioArchivo = other.tamanioArchivo;
        tamanioComprimido = other.tamanioComprimido;
        return *this;
    }
    bool   operator <(const TipoArchivo &other) const { return (nombreDelArchivo < other.getNombreDelArchivo()); }

private:
    QString nombreDelArchivo;
    QString tipoArchivo;
    double tamanioArchivo;
    double tamanioComprimido;  
};

#endif // TIPOARCHIVO_H
