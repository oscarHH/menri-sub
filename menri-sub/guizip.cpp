#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>
#include <QDebug>
//#include <QDesktopServices>
#include <QMessageBox>




/*
 *****************************************************
 *****************************************************
 *                   Metodos                         *
 *****************************************************
 *****************************************************
*/

//constructor
GuiZip::GuiZip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiZip)
{
    ui->setupUi(this);
    ui->txtComentarios->setEnabled(false);
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(QStringList () <<"Nombre"<<"Tamaño"<<"Comprimido"<<"Tipo");
    vs = new visor();
    fileZip = new ManejoZip(this);
    msgBox = new QMessageBox;
    connect(fileZip,SIGNAL(valor(unsigned int)),this,SLOT(porcentaje(unsigned int)));
    connect(fileZip,SIGNAL(finished()),this,SLOT(mensajes()));
}
//destructor
GuiZip::~GuiZip()
{
    delete ui;
}

//limpa los elementos graficos
void GuiZip::limpiar()
{
    ui->btnDescomprimir->setEnabled(false);
    ui->btnDescomprimirIndividual->setEnabled(false);
    ui->btnvisualizar->setEnabled(false);
    ui->txtComentarios->clear();
    ui->treeWidget->clear();
}

//activa los botones
void GuiZip::activar(){
    ui->btnDescomprimir->setEnabled(true);
    ui->btnDescomprimirIndividual->setEnabled(true);
    ui->btnvisualizar->setEnabled(true);
}


//agregar ramas
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
        //limpiamos las  listas
        tip.clear();
        tip = resp;
        resp.clear();
    }

    //no es carpeta
    if(!esRaiz){
        if( !nombre.contains("/")   && !nombre.contains("\\")   ){
            itm = new QTreeWidgetItem(ui->treeWidget);
            itm->setText(0,nombre);
            itm->setText(1,tamanio);
            itm->setText(2,comprimido);
            itm->setText(3,tipo);
            tip.removeAt(index);
            resp = tip;
            tip.clear();
            tip = resp;
            resp.clear();
        }
    }
}


//sub-ramas
void GuiZip::AddChild(QTreeWidgetItem *parent , QString nombre,QString tamanio,QString comprimido,QString tipo){
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,nombre);
    itm->setText(1,tamanio);
    itm->setText(2,comprimido);
    itm->setText(3,tipo);
    parent->addChild(itm);
}


/*
 *****************************************************
 *****************************************************
 *                      Slots                        *
 *****************************************************
 *****************************************************
*/


//abrir  archivo comprimido
void GuiZip::on_btnAbrir_clicked()
{
    //obtencion del archivo comprimido
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"),0, QFileDialog::DontUseNativeDialog);

    if(fileName.isEmpty()){
        return;
    }

    //verificamos el tipo de archivo
    if(fileName.endsWith(".zip") ){
        //limpia los  Widgets
        limpiar();
        //asigna nombre del archivo zip
        fileZip->setArchivoZip(fileName);
        //almacena los datos de los archivos comprimidos
        respaldoDatosComprimidos = fileZip->getListarArchivos();
        tip = fileZip->getListarArchivos();
        //Agrega todos los archivos al arbol
        while(!tip.isEmpty()){
            //si es directorio
            if(tip.at(0).getTipoArchivo() == "directorio" ){
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),true,0);

            }else{
                //si no es drectorio*
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),false,0);
            }
        }
        //adapta el tamaño de la columna 0 del Qtreview
        ui->treeWidget->resizeColumnToContents(0);

        //obtencion de los comentarios del zip
        if(fileZip->getComentarios().isEmpty()){
            ui->txtComentarios->setEnabled(false);
        }else{
            ui->txtComentarios->setEnabled(true);
            ui->txtComentarios->setPlainText(fileZip->getComentarios());
        }
        //activa los botones
        activar();
    }
    else if(fileName.endsWith(".rar")){
        /*  si es un archivo rar  */
    }

}

//descomprimir todo el contenido del archivo zip
void GuiZip::on_btnDescomprimir_clicked()
{
    //obtencion de la ruta del directorio
    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::rootPath(),QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

    directorio.replace("/",QDir::separator());

    //el string no debe estar vacio
    if(directorio.isEmpty() ){return;}
    //asigna nombre del archivo comprimido
    fileZip->setArchivoZip(fileName);
    //agrega un rango a QProgressbar
    ui->progressBar->setRange(1,fileZip->totalArchivos);
    //ruta descompresion
    if( directorio.endsWith(QDir::separator()) ){
        fileZip->setRutaDescompresion(directorio);
    }else if(!directorio.endsWith(QDir::separator())){
        fileZip->setRutaDescompresion(directorio+QDir::separator());
    }
    //inicio del hilo
    fileZip->start(QThread::LowestPriority);
}

//descompresion de archivos individuales
void GuiZip::on_btnDescomprimirIndividual_clicked()
{
 /*   QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::homePath(),QFileDialog::ShowDirsOnly| QFileDialog::DontUseNativeDialog);

    directorio.replace("/",QDir::separator());

    if(!directorio.isEmpty() && directorio.endsWith(QDir::separator()) ){
        descompreionIndividual(posicion,fileName,directorio);
    }else if(!directorio.isEmpty()  && !directorio.endsWith(QDir::separator())){
        descompreionIndividual(posicion,fileName,directorio+QDir::separator());
    }*/

}

//visualizar archivos
void GuiZip::on_btnvisualizar_clicked()
{
    //visualizarImagen(posicion,fileName);
}

//detiene la descompresion del archivo
void GuiZip::on_brnDetener_clicked()
{
    fileZip->detenerHilo();
    ui->progressBar->setValue(0);
}

//mostrar mensaje
void GuiZip::mensajes()
{
    msgBox->setText("Archivo descomprimido");
    msgBox->setWindowModality(Qt::ApplicationModal);
    msgBox->setModal(true);
    msgBox->show();
    ui->progressBar->setValue(0);
}

//muestra el progreso descompresion
void GuiZip::porcentaje(unsigned int i)
{
    ui->progressBar->setValue(i);
}

//obtiene el contenido seleccionado del arbol
void GuiZip::on_treeWidget_itemClicked(QTreeWidgetItem *item /*int column*/)
{
    qDebug()<<item->text(0);
}



/*
 *****************************************************
 *****************************************************
 * Metodos para el manejo de archivos zip            *
 *****************************************************
 *****************************************************
*/



//metodo para listar los archivos
/*void GuiZip::ListarArchivos()
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
}*/

//@parametro nombre del zip, ruta descompresion
/*void GuiZip::descomPrimirZip(QString archivo,QString rutaDescompresion)
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
}*/

//@parametro nombre del archivo a descomprimir,nombre del zip, ruta descompresion
/*void GuiZip::descompreionIndividual(int index,QString archivo,QString rutaDescompresion)
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
}*/






