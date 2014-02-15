#ifndef GUIZIP_H
#define GUIZIP_H

#include <QDialog>
#include <QWidget>
#include <quazipfile.h>
#include <quazip.h>
#include <QTreeWidget>
#include <QMessageBox>
#include "visor.h"
#include "manejozip.h"
#include <QtWebKit>
#include <QtWebKitWidgets/QWebView>

QT_BEGIN_NAMESPACE
class visor;
//class WebCore;
class webview;

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


private slots:
    void on_btnAbrir_clicked();
    void on_btnDescomprimir_clicked();
    void on_btnDescomprimirIndividual_clicked();
    void on_btnvisualizar_clicked();
    void mensajes();
    void porcentaje(unsigned int i);
    void on_brnDetener_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item /*int column*/);
    void imagen(QPixmap p);
    void on_treeWidget_clicked(const QModelIndex &index);

private:
    Ui::GuiZip *ui;
    void limpiar();
    void activar();
    void AddRoot(QString nombre,QString tamanio,QString comprimido,QString tipo,bool esRaiz,int index);
    void AddChild(QTreeWidgetItem *parent , QString nombre,QString tamanio,QString comprimido,QString tipo);
    QString respaldo;
    QStringList listaArchivos;
    int posicion ;
    QString fileName;
    ManejoZip *fileZip;
    QTreeWidgetItem *itm;
    QList <TipoArchivo> tip;
    QList <TipoArchivo> respalcarpertas;
    QMessageBox *msgBox;
    visor *vs;
    QPixmap p;
    QString archivoIndividualcomprimido;
    QString tipoArchivo;
};

#endif // GUIZIP_H
