#ifndef MANEJODEARCHIVOSTXT_H
#define MANEJODEARCHIVOSTXT_H

#include <QObject>
#include <QTextStream>

class ManejoDearchivosTxt : public QObject
{
    Q_OBJECT
public:

    QString ruta;
    QString rutaGuardar;
    //metodos constructor
    //explicit ManejoDearchivosTxt(QObject *parent = 0);
    ManejoDearchivosTxt (QString ruta);
    //asignamos ruta del archivo abrir
    void setRutaArchivo(QString ruta);
    //asignamos la ruta para guardar archivo
    void setRutaGuardar(QString ruta);
    QString getRutaArchivos();
    //metodo lectura de archivo txt
    QString leerArchivo();
    //metodo que guardara a un txt
    bool archivoGuardar(QString datos);

    QStringList leerRutas(QString rut);

signals:

public slots:

};

#endif // MANEJODEARCHIVOSTXT_H
