#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>

GuiZip::GuiZip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiZip)
{
    ui->setupUi(this);
    manejozip = new EventosZip();
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
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(),tr("Archivo comprimido (*.zip)"));

    if( !fileName.isEmpty()){
        //limpia la lista
        ui->jlArchivos->clear();
        ui->txtComentarios->setEnabled(false);
        ui->txtComentarios->setPlainText("");
        //asignamos la ruta
        manejozip->setListar(fileName);
        //obtenemos los comentarios
        if(!manejozip->getComentario().isEmpty()){
            ui->txtComentarios->setEnabled(true);
            ui->txtComentarios->setPlainText(manejozip->getComentario());
        }

        //obtenemos los archivos
        QStringList ren = manejozip->getListarzip();
        //mostramos la lista de archivos
        for(int i=0; i < ren.size();i++){
            ui->jlArchivos->addItem(ren.at(i));
        }
        ui->btnDescomprimir->setEnabled(true);
    }
}


//descomprimir
void GuiZip::on_btnDescomprimir_clicked()
{
    QString directorio = QFileDialog::getExistingDirectory(this,
                                                           tr("Seleccione el Directorio"),
                                                           QDir::homePath(),
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
    if(!directorio.isEmpty()){
        manejozip->descomprimir(fileName,directorio+"/");
    }

}
