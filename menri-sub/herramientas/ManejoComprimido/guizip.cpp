#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>
#include <QDebug>
//#include <QDesktopServices>
#include <QMessageBox>
#include <QMovie>

#include <QWebElement>
#include <QTextStream>
#include <QSslSocket>
#include <QDir>

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


    //QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    //QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
    //QWebSettings::globalSettings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
    //QWebSettings::globalSettings()->setAttribute(QWebSettings::CSSGridLayoutEnabled, true);
    //QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    //QNetworkProxyFactory::setUseSystemConfiguration (true);
    //ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    // ui->webView->load(QUrl("http://google.com"));


    vs = new visor();
    fileZip = new ManejoZip(this);
    msgBox = new QMessageBox;
    connect(fileZip,SIGNAL(valor(unsigned int)),this,SLOT(porcentaje(unsigned int)));
    connect(fileZip,SIGNAL(finished()),this,SLOT(mensajes()));
    connect(fileZip,SIGNAL(imagen(QPixmap)),this,SLOT(imagen(QPixmap)));


}
//destructor
GuiZip::~GuiZip()
{
    delete vs;
    delete fileZip;
    delete itm;
    delete ui;
    delete msgBox;
}

//limpa los elementos graficos
void GuiZip::limpiar()
{
    ui->btnDescomprimir->setEnabled(false);
    ui->btnDescomprimirIndividual->setEnabled(false);
    ui->btnvisualizar->setEnabled(false);
    ui->txtComentarios->clear();
    ui->treeWidget->clear();
    respalcarpertas.clear();
    tip.clear();
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

    for(int i=0; i < tip.size() ;i++){
        if(tip.at(i).getTipoArchivo() == "directorio" ){
            respalcarpertas.append(tip.at(i));
            continue;
        }
        if(tip.at(i).getTipoArchivo() != "directorio" ){
            //agregamos la carpeta
            itm = new QTreeWidgetItem(ui->treeWidget);
            itm->setText(0,tip.at(i).getNombreDelArchivo());
            itm->setText(1,QString::number(tip.at(i).getTamanioArchivo()));
            itm->setText(2,QString::number(tip.at(i).getTamanioComprimido()));
            itm->setText(3,tip.at(i).getTipoArchivo());
            continue;
        }


        /*if(tip.at(i).getTipoArchivo() == "directorio"  && tip.at(i).getNombreDelArchivo().startsWith( nombreCarpeta )){
            AddChild(itm,tip.at(i).getNombreDelArchivo(),QString::number(tip.at(i).getTamanioArchivo()),QString::number(tip.at(i).getTamanioComprimido()),tip.at(i).getTipoArchivo());
            //hijo->setText(0,tip.at(i).getNombreDelArchivo());
           // hijo->setText(1,QString::number(tip.at(i).getTamanioArchivo()));
           // hijo->setText(2,QString::number(tip.at(i).getTamanioComprimido()));
            //hijo->setText(3,tip.at(i).getTipoArchivo());
            //itm->addChild(hijo);
            respalcarpertas.append(tip.at(i));
            continue;
        }else  if (tip.at(i).getTipoArchivo() != "directorio" && tip.at(i).getNombreDelArchivo().startsWith( nombreCarpeta )){
            AddChild(itm,tip.at(i).getNombreDelArchivo(),QString::number(tip.at(i).getTamanioArchivo()),QString::number(tip.at(i).getTamanioComprimido()),tip.at(i).getTipoArchivo());
            continue;
        }*/
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
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"),0);

    if(fileName.isEmpty()){
        return;
    }

    //verificamos el tipo de archivo
    if(fileName.endsWith(".zip") ){
        limpiar();
        //asigna nombre del archivo zip
        fileZip->setArchivoZip(fileName);
        //almacena los datos de los archivos comprimidos
        tip = fileZip->getListarArchivos();
        //Agrega todos los archivos al arbol
        /*while(!tip.isEmpty()){
            //si es directorio
            if(tip.at(0).getTipoArchivo() == "directorio" ){
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),true,0);
            }else{
                //si no es drectorio*
                AddRoot(tip.at(0).getNombreDelArchivo(),QString::number(tip.at(0).getTamanioArchivo()) ,QString::number(tip.at(0).getTamanioComprimido()),tip.at(0).getTipoArchivo(),false,0);
            }
        }*/

       AddRoot("w","w","w","e",true,0);


        /*foreach (TipoArchivo ti , tip){
            qDebug()<<ti.getNombreDelArchivo();
        }*/


        //adapta el tamaño de la columna 0 del Qtreview
        ui->treeWidget->resizeColumnToContents(0);

        //obtencion de los comentarios del zip
        if(fileZip->getComentarios().isEmpty()){
            ui->txtComentarios->setEnabled(false);
        }else{
            ui->txtComentarios->setEnabled(true);
            ui->txtComentarios->setText(fileZip->getComentarios());

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
    QDir crearCarpeta;


    //asigna nombre del archivo comprimido
    fileZip->setArchivoZip(fileName);
    fileZip->setOpcion(1);
    //agrega un rango a QProgressbar
    ui->progressBar->setRange(0,fileZip->totalArchivos);
    //ruta descompresion
    if( directorio.endsWith(QDir::separator()) ){
        fileZip->setRutaDescompresion(directorio);
        //crea las carpetas
        foreach (TipoArchivo  tp , respalcarpertas) {
            crearCarpeta.mkpath(directorio + tp.getNombreDelArchivo());
        }
    }else if(!directorio.endsWith(QDir::separator())){
        fileZip->setRutaDescompresion(directorio+QDir::separator());
        //crea las carpetas
        foreach (TipoArchivo  tp , respalcarpertas) {
            crearCarpeta.mkpath(directorio + QDir::separator() + tp.getNombreDelArchivo());
        }
    }
    //inicio del hilo
    fileZip->start(QThread::LowestPriority);
}

//descompresion de archivos individuales
void GuiZip::on_btnDescomprimirIndividual_clicked()
{

    QString directorio = QFileDialog::getExistingDirectory(this,tr("Descomprimir en"), QDir::homePath(),QFileDialog::ShowDirsOnly| QFileDialog::DontUseNativeDialog);

    directorio.replace("/",QDir::separator());
    fileZip->setArchivoZip(fileName);
    fileZip->setOpcion(2);
    if(directorio.isEmpty() || archivoIndividualcomprimido.isEmpty() ){return;}
    ui->progressBar->setRange(0,3);
    QFileInfo info1 (archivoIndividualcomprimido);
    QDir carpeta;


    fileZip->setNombreArchivo(archivoIndividualcomprimido);

    if(directorio.endsWith(QDir::separator()) ){

        if(archivoIndividualcomprimido.contains("/")){
            carpeta.mkpath(directorio +  info1.path().replace("/",QDir::separator()));
        }

        fileZip->setRutaDescompresion(directorio);

    }else if(!directorio.endsWith(QDir::separator())){

        if(archivoIndividualcomprimido.contains("/")){
            carpeta.mkpath(directorio + QDir::separator() + info1.path().replace("/",QDir::separator()));
        }

        fileZip->setRutaDescompresion(directorio+QDir::separator());
    }

    fileZip->start(QThread::LowestPriority);
}

//visualizar archivos
void GuiZip::on_btnvisualizar_clicked()
{
    //si no selecciono algun archivo
    if(archivoIndividualcomprimido.isEmpty() ){return;}
    //nombre del archivo zip
    fileZip->setArchivoZip(fileName);
    //operacion a  realizar
    fileZip->setOpcion(3);
    //rango para la barra de progreso
    ui->progressBar->setRange(0,3);


    //asignamos el nombre del archivo
    fileZip->setNombreArchivo(archivoIndividualcomprimido);
    connect(fileZip,SIGNAL(finished()),msgBox,SLOT(close()) );
    if(tipoArchivo == "Imagen"){
        //inicia el hilo}
        fileZip->start(QThread::LowestPriority);
    }else{
        QDir temporal;

        if(temporal.exists( QDir::tempPath() + "/mensrisub$cross" )){
            qDebug()<<"si existe";
        }else{
            qDebug()<<"no existe";
            QString ruta = QDir::tempPath() + "/mensrisub$cross";
            temporal.mkdir(ruta);
        }


        //1.-verificar si existen  carpetas llamadas menrisub$cross+(numero aleatorio)
        //2.-verificar que la carpeta no este en uso
        //elimina la carpeta
        //generar un numero aleatorio de 5 digitos
        //crear una carpeta llamada menrisub$cross+(numero aleatorio)
        //almacenar ruta de la carpeta
        //si la carpeta esta en uso
        //no borrar
        //generar un numero aleatorio de 5 digitos
        //crear una carpeta llamada menrisub$cross+(numero aleatorio)
        //almacenar ruta de la carpeta

        //descomprimir y llamar al programa por defecto para abrir el archivo



    }

}

//detiene la descompresion del archivo
void GuiZip::on_brnDetener_clicked()
{
    fileZip->detenerHilo();
    ui->progressBar->setValue(0);
}

//muestra mensaje que desomprimio el archivo
void GuiZip::mensajes()
{
    ui->progressBar->setValue(0);
    msgBox->setText("Archivo descomprimido");
    msgBox->setWindowModality(Qt::ApplicationModal);
    msgBox->setModal(true);
    msgBox->exec();
    fileZip->detenerHilo();
    ui->btnAbrir->setEnabled(true);
    ui->btnDescomprimir->setEnabled(true);
    ui->btnDescomprimirIndividual->setEnabled(true);
    ui->btnvisualizar->setEnabled(true);
    ui->treeWidget->setEnabled(true);

}

//muestra el progreso descompresion
void GuiZip::porcentaje(unsigned int i)
{
    ui->progressBar->setValue(i);
    ui->btnAbrir->setEnabled(false);
    ui->btnDescomprimir->setEnabled(false);
    ui->btnDescomprimirIndividual->setEnabled(false);
    ui->btnvisualizar->setEnabled(false);
    ui->treeWidget->setEnabled(false);
    ui->txtComentarios->setEnabled(false);
}

//obtiene el contenido seleccionado del arbol
void GuiZip::on_treeWidget_itemClicked(QTreeWidgetItem *item /*int column*/)
{
    archivoIndividualcomprimido = item->text(0);
    tipoArchivo = item->text(3);
}

//slot para mostrar la imagen
void GuiZip::imagen(QPixmap p)
{
    vs->cargarImagen(p);
    vs->show();

}

void GuiZip::on_treeWidget_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
}


