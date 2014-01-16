#include "ui_guizip.h"
#include "guizip.h"
#include <QFileDialog>

GuiZip::GuiZip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiZip)
{
    ui->setupUi(this);
}

GuiZip::~GuiZip()
{
    delete ui;
}

void GuiZip::cargarArchivos(QString archivo)
{
    ui->jlArchivos->addItem(archivo);
}

void GuiZip::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo comprimido"), QDir::homePath(), tr("Archivo comprimido (*.zip *.gzip"));

    manejozip = new EventosZip();
    QStringList ren = manejozip->listarzip(fileName);

    for(int i=0; i < ren.size();i++){
        ui->jlArchivos->addItem(ren.at(i));
    }
}

void GuiZip::on_pushButton_2_clicked()
{
    manejozip = new EventosZip();
    manejozip->descomprimir(fileName,"F:/");
}
