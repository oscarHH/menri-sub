#ifndef MANEJODEARCHIVOSTXT_H
#define MANEJODEARCHIVOSTXT_H

#include <QObject>
#include <QTextStream>
#include <QTextCodec>

class ManejoDearchivosTxt : public QObject
{
    Q_OBJECT
public:
    QString ruta;
    //metodos constructor
    //explicit ManejoDearchivosTxt(QObject *parent = 0);
    ManejoDearchivosTxt ();
    ~ManejoDearchivosTxt ();
    //asignamos ruta del archivo abrir
    void setRutaArchivo(QString ruta);
    //asignamos la ruta para guardar archivo
    QString getRutaArchivos();
    //metodo lectura de archivo txt
    QString leerArchivo();
    //metodo que guardara a un txt
    bool archivoGuardar(QString datos);

    QStringList leerRutas(QString rut);




};

#endif // MANEJODEARCHIVOSTXT_H
