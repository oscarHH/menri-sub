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
    connect(ui->jlArchivos,SIGNAL(clicked(QModelIndex)),this,SLOT(on_listWidget_clicked(QModelIndex)));
    vs = new visor();
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
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);




    if(!directorio.isEmpty()){
        descomPrimirZip(fileName,directorio+"/");
    }
}

void GuiZip::on_listWidget_clicked(const QModelIndex &index)
{
    posicion = index.row();
    qDebug()<<posicion;

}

void GuiZip::ListarArchivos()
{

    QProgressDialog progreso(this);
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"),0, QFileDialog::DontUseNativeDialog);
    if(!fileName.isEmpty()){
        respaldo = fileName;
        progreso.setLabelText(tr("Cargando archivos de %1").arg(fileName));
        QuaZip zip(fileName);
        //se abre el archivo zip
        zip.open(QuaZip::mdUnzip);
        //obtener comentarios
         //QByteArray  encodedString =zip.getComment().unicode();
         //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
         //QTextCodec *codec =  QTextCodec::codecForLocale();
         //QString img = codec->toUnicode(encodedString);



         QByteArray comment = zip.getComment().toUtf8();
         listaArchivos = zip.getFileNameList();

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
            ui->btnDescomprimirIndividual->setEnabled(true);
            ui->btnvisualizar->setEnabled(true);
        }
    }else{
        fileName= respaldo;
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
        ba =zFile.read(1000000000);



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

//@parametro nombre del archivo a descomprimir,nombre del zip, ruta descompresion
void GuiZip::descompreionIndividual(int index,QString archivo,QString rutaDescompresion)
{

    QProgressDialog progreso(this);
    progreso.setLabelText(tr("Descomprimiendo archivo en  %1").arg(rutaDescompresion));
    QuaZip zip(archivo);
    QByteArray ba ;
    //abre el archivo
    zip.open(QuaZip::mdUnzip);
    progreso.setRange(0,2);
    progreso.setModal(true);


    //actualizamos la barra de progreso
    progreso.setValue(1);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    //nombre del zip
    QString filePath = listaArchivos.at(index);
    QuaZipFile zFile( zip.getZipName(), filePath );
    zFile.open( QIODevice::ReadOnly );
    ba =zFile.read(1000000000);
    zFile.close();
    //la ruta donde se guardara + el nobre del archivo
    QFile dstFile( rutaDescompresion+filePath );
    dstFile.open( QIODevice::WriteOnly);
    dstFile.write( ba);
    dstFile.close();
    ba.clear();
    zip.close();
}

void GuiZip::visualizarImagen(int index,QString archivo)
{
    QProgressDialog progreso(this);
    progreso.setLabelText(tr("Cargando imagen"));
    QuaZip zip(archivo);
    QByteArray ba ;
    //abre el archivo
    zip.open(QuaZip::mdUnzip);
    progreso.setRange(0,2);
    progreso.setModal(true);
    //actualizamos la barra de progreso
    progreso.setValue(1);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    //nombre del zip
    QString filePath = listaArchivos.at(index);
    QuaZipFile zFile( zip.getZipName(), filePath );
    zFile.open( QIODevice::ReadOnly );
    ba =zFile.read(1000000000);
    if(p.loadFromData(ba,"") ){
        vs->cargarImagen(p);
    }
    zFile.close();
    ba.clear();
    zip.close();
    vs->show();
}


void GuiZip::on_btnDescomprimirIndividual_clicked()
{
    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::homePath(),
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly| QFileDialog::DontUseNativeDialog);

    if(!directorio.isEmpty()){
        descompreionIndividual(posicion,fileName,directorio+"/");

    }

}

void GuiZip::on_btnvisualizar_clicked()
{
    visualizarImagen(posicion,fileName);
}
