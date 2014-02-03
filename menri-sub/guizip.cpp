#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>
#include <QProgressDialog>
#include <QDebug>
//#include <QDesktopServices>
#include <QMessageBox>



GuiZip::GuiZip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiZip)
{
    ui->setupUi(this);
    ui->txtComentarios->setEnabled(false);
    //connect(ui->jlArchivos,SIGNAL(clicked(QModelIndex)),this,SLOT(on_listWidget_clicked(QModelIndex)));
    vs = new visor();
    ui->treeWidget->setColumnCount(4);
    QStringList a;
    a<<"Nombre"<<"Tamaño"<<"Comprimido"<<"Tipo";
    ui->treeWidget->setHeaderLabels(a);
}

GuiZip::~GuiZip()
{
    delete ui;
}

//metodo para agregar  padre al arbol
void GuiZip::AddRoot(QString nombre,QString tamanio,QString comprimido,QString tipo,bool esRaiz,int index)
{
     QList<TipoArchivo> resp;
    //si es una carpeta
    if(esRaiz == true){
        itm = new QTreeWidgetItem(ui->treeWidget);
        //agregamos la carpeta
        itm->setText(0,nombre);
        itm->setText(1,tamanio);
        itm->setText(2,comprimido);
        itm->setText(3,tipo);

        //agregamos las ramas
        for(int i = 0; i < tip.size();i++){
            if( !tip.at(i).getNombreDelArchivo().startsWith(nombre)){
                resp.append(tip.at(i));
            }
            //si la rama contiene el nombre de la carpeta se agrega
            if(tip.at(i).getNombreDelArchivo().startsWith(nombre) && tip.at(i).getTipoArchivo() !="directorio"){
                AddChild(itm, tip.at(i).getNombreDelArchivo(),QString::number(tip.at(i).getTamanioArchivo()) ,QString::number(tip.at(i).getTamanioComprimido()),tip.at(i).getTipoArchivo());
            }
        }
        tip.clear();
        tip = resp;
        resp.clear();
    }

    if(!esRaiz){
        if( !nombre.contains("/")   && !nombre.contains("\\")   ){
            itm = new QTreeWidgetItem(ui->treeWidget);
            itm->setText(0,nombre);
            itm->setText(1,tamanio);
            itm->setText(2,comprimido);
            itm->setText(3,tipo);
           // qDebug()<<"aaa::::"<<nombre;
            tip.removeAt(index);
            resp = tip;
            tip.clear();
            tip = resp;
            resp.clear();
        }

    }

   /* foreach(TipoArchivo j , tip){
        qDebug()<<"------------"<<j.getNombreDelArchivo();
    }*/

}


//agrega una rama  al arbol
void GuiZip::AddChild(QTreeWidgetItem *parent , QString nombre,QString tamanio,QString comprimido,QString tipo){
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,nombre);
    itm->setText(1,tamanio);
    itm->setText(2,comprimido);
    itm->setText(3,tipo);
    parent->addChild(itm);
}


//boton abrir el archivo comprimido
void GuiZip::on_btnAbrir_clicked()
{
    //ListarArchivos();

    //obtencion del archivo comprimido
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"),0, QFileDialog::DontUseNativeDialog);

    //verificamos el tipo de archivo
    if(fileName.endsWith(".zip") &&  !fileName.isEmpty()){
        limpiar();
        //asigna nombre del archivo zip
        fileZip.setArchivoZip(fileName);
        //almacena los datos de los archivos comprimidos
        respaldoDatosComprimidos = fileZip.getListarArchivos();
        tip = fileZip.getListarArchivos();
        //qDebug()<<tip.size();
        /*for(int i =0; i < tip.size();++i){
            //si es directorio
            if(tip.at(i).getTipoArchivo() == ("directorio") ){
                AddRoot(tip.at(i).getNombreDelArchivo(),QString::number(tip.at(i).getTamanioArchivo()) ,QString::number(tip.at(i).getTamanioComprimido()),tip.at(i).getTipoArchivo(),true,i);

            }else{
                //si no es drectorio*
                AddRoot(tip.at(i).getNombreDelArchivo(),QString::number(tip.at(i).getTamanioArchivo()) ,QString::number(tip.at(i).getTamanioComprimido()),tip.at(i).getTipoArchivo(),false,i);
            }
             i=0;
            qDebug()<<i;
            qDebug()<<tip.size()<<tip.at(i).getNombreDelArchivo();
        }*/

        while(!tip.isEmpty()){
            //si es directorio
            if(tip.at(0).getTipoArchivo() == ("directorio") ){
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),true,0);

            }else{
                //si no es drectorio*
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),false,0);
            }
        }


        //obtencion de los comentarios del zip
        if(fileZip.getComentarios().isEmpty()){
            ui->txtComentarios->setEnabled(false);
        }else{
            ui->txtComentarios->setEnabled(true);
            ui->txtComentarios->setPlainText(fileZip.getComentarios());
        }
        /*  si es un archivo rar  */
    }else if(fileName.endsWith(".rar")){

    }
}

//boton descomprimir
void GuiZip::on_btnDescomprimir_clicked()
{
    //obtencion de la ruta del directorio
    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::rootPath(),
                                                           QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
    directorio.replace("/",QDir::separator());

    if(!directorio.isEmpty() && directorio.endsWith(QDir::separator()) ){
        //descompreionIndividual(posicion,fileName,directorio);
        descomPrimirZip(fileName,directorio);
    }else if(!directorio.isEmpty()  && !directorio.endsWith(QDir::separator())){
        //descompreionIndividual(posicion,fileName,directorio+QDir::separator());
        descomPrimirZip(fileName,directorio+QDir::separator());
    }

}

//boton descompresion de archivos individuales
void GuiZip::on_btnDescomprimirIndividual_clicked()
{
    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::homePath(),QFileDialog::ShowDirsOnly| QFileDialog::DontUseNativeDialog);

    directorio.replace("/",QDir::separator());

    if(!directorio.isEmpty() && directorio.endsWith(QDir::separator()) ){
        descompreionIndividual(posicion,fileName,directorio);
    }else if(!directorio.isEmpty()  && !directorio.endsWith(QDir::separator())){
        descompreionIndividual(posicion,fileName,directorio+QDir::separator());
    }

}

//visualiza la imagen
void GuiZip::on_btnvisualizar_clicked()
{
    visualizarImagen(posicion,fileName);
}


//obtencion del index del listview
void GuiZip::on_listWidget_clicked(const QModelIndex &index)
{
    posicion = index.row();
    qDebug()<<posicion;

}


/*
 *****************************************************
 *****************************************************
 * Metodos para el manejo de archivos zip            *
 *****************************************************
 *****************************************************
*/



//metodo para listar los archivos
void GuiZip::ListarArchivos()
{

    QProgressDialog progreso(this);
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"),0, QFileDialog::DontUseNativeDialog);

    if(!fileName.isEmpty()){
        int i=0;

        respaldo = fileName;
        progreso.setLabelText(tr("Cargando archivos de %1").arg(fileName));
        QuaZip zip(fileName);
        //se abre el archivo zip
        zip.open(QuaZip::mdUnzip);

        //informacion del zip
        QuaZipFile inf(&zip);
        zip.setCommentCodec(QTextCodec::codecForLocale());
        //obtener comentario
        QByteArray comment = zip.getComment().toUtf8();
        listaArchivos = zip.getFileNameList();
        if( !listaArchivos.isEmpty()){
            //limpia la lista
            //ui->jlArchivos->clear();
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
            for(bool more=zip.goToFirstFile();more;more = zip.goToNextFile()){
                //actualizamos la barra de progreso
                progreso.setValue(i);
                qApp->processEvents();

                if(progreso.wasCanceled()){
                    //ui->jlArchivos->clear();
                    break;
                    zip.close();
                }

                //ui->jlArchivos->addItem(listaArchivos.at(i));
                i++;
                //informacion de archivos comprimidos
                inf.open(QIODevice::ReadOnly);
                qDebug()<<inf.csize();
                inf.close();
            }

            zip.close();
            ui->btnDescomprimir->setEnabled(true);
            ui->btnDescomprimirIndividual->setEnabled(true);
            ui->btnvisualizar->setEnabled(true);

        }
    }else{
        fileName= respaldo;
    }
}

//@parametro nombre del zip, ruta descompresion
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
        ba =zFile.read(zFile.size());

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
    //QString filePath = listaArchivos.at(index)
    QuaZipFile zFile( zip.getZipName(), listaArchivos.at(index) );
    zFile.open( QIODevice::ReadOnly );
    ba = zFile.read(zFile.size());
    //qDebug()<<"tamño del archivo="<<zFile.size();
    zFile.close();
    //la ruta donde se guardara + el nobre del archivo
    QFile dstFile( rutaDescompresion+listaArchivos.at(index) );
    dstFile.open( QIODevice::WriteOnly);
    dstFile.write( ba);
    dstFile.close();
    ba.clear();
    zip.close();
}

//@parametro indice del archivo, nombre del zip
void GuiZip::visualizarImagen(int index,QString archivo)
{

    if(listaArchivos.at(index).endsWith(".jpg") ||
            listaArchivos.at(index).endsWith(".png") ||
            listaArchivos.at(index).endsWith(".psd") ||
            listaArchivos.at(index).endsWith(".svg") ||
            listaArchivos.at(index).endsWith(".bmp") ||
            listaArchivos.at(index).endsWith(".jpeg") ){
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
        //QString filePath = listaArchivos.at(index);
        QuaZipFile zFile( zip.getZipName(), listaArchivos.at(index) );
        zFile.open( QIODevice::ReadOnly );
        ba =zFile.read(zFile.size());
        if(p.loadFromData(ba,"") ){
            vs->cargarImagen(p);
        }
        zFile.close();
        zip.close();
        ba.clear();
        vs->show();
    }
}

void GuiZip::limpiar()
{
    ui->btnDescomprimir->setEnabled(false);
    ui->btnDescomprimirIndividual->setEnabled(false);
    ui->btnvisualizar->setEnabled(false);
    ui->txtComentarios->clear();
    ui->treeWidget->clear();
}

