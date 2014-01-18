#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>
#include <QProgressDialog>
#include <QDebug>
GuiZip::GuiZip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiZip)
{
    ui->setupUi(this);
    ui->txtComentarios->setEnabled(false);
}

GuiZip::~GuiZip()
{
    delete ui;
}

void GuiZip::cargarArchivos(QString archivo)
{
    ui->jlArchivos->addItem(archivo);
}



//abrir el archivo comprimido
void GuiZip::on_btnAbrir_clicked()
{
    ListarArchivos();
}


//descomprimir
void GuiZip::on_btnDescomprimir_clicked()
{
    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::homePath(),
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if(!directorio.isEmpty()){
        descomPrimirZip(fileName,directorio+"/");
    }
}

void GuiZip::ListarArchivos()
{
    QProgressDialog progreso(this);
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"));
    progreso.setLabelText(tr("Cargando archivos de %1").arg(fileName));
    QuaZip zip(fileName);
    //se abre el archivo zip
    zip.open(QuaZip::mdUnzip);
    //obtener comentarios
    QByteArray comment = zip.getComment().toLatin1();
    QStringList listaArchivos = zip.getFileNameList();
    zip.close();
    if( !listaArchivos.isEmpty()){
        //limpia la lista
        ui->jlArchivos->clear();
        ui->txtComentarios->setEnabled(false);
        ui->txtComentarios->setPlainText("");

        //obtenemos los comentarios
        if(!comment.isEmpty()){
            ui->txtComentarios->setEnabled(true);
            ui->txtComentarios->setPlainText(comment);
        }
        //obtenemos los archivos

        progreso.setRange(0,listaArchivos.size());
        progreso.setModal(true);
        //mostramos la lista de archivos
        for(int i=0; i < listaArchivos.size();i++){
            //actualizamos la barra de progreso
            progreso.setValue(i);
            qApp->processEvents();
            if(progreso.wasCanceled()){
                ui->jlArchivos->clear();
            }
            ui->jlArchivos->addItem(listaArchivos.at(i));
        }
        ui->btnDescomprimir->setEnabled(true);
    }
}

void GuiZip::descomPrimirZip(QString archivo,QString rutaDescompresion)
{
    int i = 1;
    QProgressDialog progreso(this);
    progreso.setLabelText(tr("Descomprimiendo archivos en  %1").arg(rutaDescompresion));
    QuaZip zip(archivo);
    QByteArray ba ;
    //abre el archivo
    zip.open(QuaZip::mdUnzip);
    progreso.setRange(0,zip.getEntriesCount()+1);
    progreso.setModal(true);
    for(bool more = zip.goToFirstFile();more ;more = zip.goToNextFile()){

        //actualizamos la barra de progreso
        progreso.setValue(i);
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        if(progreso.wasCanceled()){
            break;
        }
        //nombre del zip
        QString filePath = zip.getCurrentFileName();
        QuaZipFile zFile( zip.getZipName(), filePath );
        zFile.open( QIODevice::ReadOnly );
        ba =""+ zFile.read(1000000000);
        zFile.close();
        //la ruta donde se guardara + el nobre del archivo
        QFile dstFile( rutaDescompresion+filePath );
        dstFile.open( QIODevice::WriteOnly);
        dstFile.write( ba);
        dstFile.close();
        ba.clear();
        i++;
    }
    zip.close();
}
