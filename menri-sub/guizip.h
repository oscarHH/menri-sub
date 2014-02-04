#ifndef GUIZIP_H
#define GUIZIP_H

#include <QDialog>
#include <QWidget>
#include <quazipfile.h>
#include <quazip.h>
#include "visor.h"
#include "manejozip.h"
#include <QTreeWidget>
QT_BEGIN_NAMESPACE
class DialogOptionsWidget;
class visor;
QT_END_NAMESPACE

namespace Ui {
class GuiZip;
}

class GuiZip : public QDialog
{
    Q_OBJECT

public:
    explicit GuiZip(QWidget *parent = 0);
    ~GuiZip();

    QString fileName;
    visor *vs;
    QPixmap p;
    ManejoZip fileZip;
    QTreeWidgetItem *itm;
    void AddRoot(QString nombre,QString tamanio,QString comprimido,QString tipo,bool esRaiz,int index);
    QList <TipoArchivo> tip;
    QList <TipoArchivo> respaldoDatosComprimidos;
    void AddChild(QTreeWidgetItem *parent , QString nombre,QString tamanio,QString comprimido,QString tipo);
private slots:
    void on_btnAbrir_clicked();
    void on_btnDescomprimir_clicked();
    void on_listWidget_clicked(const QModelIndex &index);
    void on_btnDescomprimirIndividual_clicked();
    void on_btnvisualizar_clicked();

private:
    Ui::GuiZip *ui;
    DialogOptionsWidget *fileDialogOptionsWidget;
    void ListarArchivos();
    void descomPrimirZip(QString archivo,QString rutaDescompresion);
    void descompreionIndividual(int index,QString archivo,QString rutaDescompresion);
    void visualizarImagen(int index,QString archivo);
    void limpiar();
    void activar();
    QString respaldo;
    QStringList listaArchivos;
    int posicion ;


};

#endif // GUIZIP_H
