#include "agregarnuevapalabra.h"
#include "ui_agregarnuevapalabra.h"
#include <QColorDialog>

AgregarNuevaPalabra::AgregarNuevaPalabra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarNuevaPalabra)
{
    ui->setupUi(this);
    ui->txtColor->setPalette(Qt::black);
}

AgregarNuevaPalabra::~AgregarNuevaPalabra()
{
    delete ui;
}

//cierra el dialogo
void AgregarNuevaPalabra::on_btnCancelar_clicked()
{
    this->close();
}

//escribe palabra
void AgregarNuevaPalabra::on_txtPalabra_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->btnAceptar->setEnabled(false);
    }else{
        ui->btnAceptar->setEnabled(true);
    }

}

//selecciona color
void AgregarNuevaPalabra::on_btnColor_clicked()
{
  color = QColorDialog::getColor(Qt::white,this,"color de letra");

  if(color.isValid()){
     ui->txtColor->setPalette(color);
  }else{
      return;
  }
}

//boton aceptar
void AgregarNuevaPalabra::on_btnAceptar_clicked()
{
    dconfig.setPalabra(ui->txtPalabra->text());
    dconfig.setColor(color);
    accept();
}
