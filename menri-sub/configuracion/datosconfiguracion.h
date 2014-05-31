#ifndef DATOSCONFIGURACION_H
#define DATOSCONFIGURACION_H

#include <QString>
#include <QColor>

class datosConfiguracion
{
    QString palabra;
    QColor color;
public:
    datosConfiguracion(): palabra(""),color(""){}
    void setPalabra(const QString &mPalabra) {palabra = mPalabra;}
    void setColor(const QColor &mColor) {color = mColor;}
    QString getPalabra() const {return palabra;}
    QColor getCOlor() const {return color;}
};

#endif // DATOSCONFIGURACION_H
