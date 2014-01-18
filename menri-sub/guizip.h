#ifndef GUIZIP_H
#define GUIZIP_H

#include <QDialog>
#include <QWidget>
#include <JlCompress.h>
#include <quazipfile.h>
#include <quazip.h>
#include <zip.h>
QT_BEGIN_NAMESPACE
class EventosZip;
class DialogOptionsWidget;
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
    void cargarArchivos(QString archivo);
    QString fileName;

private slots:
    void on_btnAbrir_clicked();
    void on_btnDescomprimir_clicked();

private:
    Ui::GuiZip *ui;
    EventosZip *manejozip;
    DialogOptionsWidget *fileDialogOptionsWidget;
    void ListarArchivos();
    void descomPrimirZip(QString archivo,QString rutaDescompresion);
};

#endif // GUIZIP_H
